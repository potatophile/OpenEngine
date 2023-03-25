#include "Engine/Game.h"
#include "Engine/Graphics/Mesh.h"
#include "Engine/Graphics/GraphicsEngine.h"
#include "Engine/Input.h"
#include "Engine/Graphics/Camera.h"

Game& Game::GetGameInstance()
{
    static Game* GameInstance = new Game();
    return *GameInstance;
}

void Game::DestroyGameInstance()
{
    static Game* GameInstance = &GetGameInstance();

    delete GameInstance;
}

Game::Game()
{
    cout << "Game Initialized" << endl;

    Graphics = nullptr;
    bIsGameOver = false;
}

Game::~Game()
{
    //since nothing else is storing the graphics in memory
    //this will destroy the graphics from the memory
    Graphics = nullptr;

    cout << "Game Over..." << endl;
}

void Game::Start(const char* WTitle, bool bFullscreen, int WWidth, int WHeight)
{
    //Load the window using graphics class
    Graphics = make_shared<GraphicsEngine>();

    //if the window fails to load then bIsGameOver = true
    if (!Graphics->InitGE(WTitle, bFullscreen, WWidth, WHeight)) {
        bIsGameOver = true;
    }

    Run();
}

void Game::Run()
{
    if (!bIsGameOver) {
        //create an input object to detect input
        GameInput = new Input();

        //create a shader
        ShaderPtr TextureShader = Graphics->CreateShader({
            L"Game/Shader/TextureShader/TextureShader.svert",
            L"Game/Shader/TextureShader/TextureShader.sfrag"
            });
        
        //create textures
        TexturePtr TBlueTiles = Graphics->CreateTexture("Game/Textures/BlueTiles.jpg");
        TexturePtr TGreenMosaic = Graphics->CreateTexture("Game/Textures/GreenMosaic.jpg");
        TexturePtr TUVMAP = Graphics->CreateTexture("Game/Textures/UVMapping.jpg");
        TexturePtr TSpongeBob = Graphics->CreateTexture("Game/Textures/Spongebob.jpg");

        //create meshes with two textures blended together
        Poly = Graphics->CreateSimpleMeshShape(GeometricShapes::Cube, TextureShader, { TBlueTiles, TGreenMosaic });
        Poly2 = Graphics->CreateSimpleMeshShape(GeometricShapes::Cube, TextureShader, { TUVMAP, TSpongeBob });
        
        //polygons with unique texture assigned to individual mesh
        MeshPtr Texture1 = Graphics->CreateSimpleMeshShape(GeometricShapes::Polygon, TextureShader, { TBlueTiles });
        MeshPtr Texture2 = Graphics->CreateSimpleMeshShape(GeometricShapes::Polygon, TextureShader, { TGreenMosaic });
        MeshPtr Texture3 = Graphics->CreateSimpleMeshShape(GeometricShapes::Polygon, TextureShader, { TUVMAP });
        MeshPtr Texture4 = Graphics->CreateSimpleMeshShape(GeometricShapes::Polygon, TextureShader, { TSpongeBob });
        //test->Transform.Rotation.y = 60.0f;

        //initial transformations for the meshes
        Poly->Transform.Location = Vector3(0.0f, 0.0f, 0.5f);
        Poly2->Transform.Location = Vector3(0.0f, 0.0f, -0.5f);

        //polygons translated to each corner of the screen
        Texture1->Transform.Location = Vector3(0.0f, 1.0f, -2.0f);
        Texture1->Transform.Rotation.y = 90.0f;

        Texture2->Transform.Location = Vector3(0.0f, 1.0f, 2.0f);
        Texture2->Transform.Rotation.y = 90.0f;
        
        Texture3->Transform.Location = Vector3(0.0f, -1.0f, -2.0f);
        Texture3->Transform.Rotation.y = 90.0f;
        
        Texture4->Transform.Location = Vector3(0.0f, -1.0f, 2.0f);
        Texture4->Transform.Rotation.y = 90.0f;


        //Tri->Transform.Location.x = -0.5f;
        //Poly->Transform.Rotation.z = 45.0f;
        //Poly->Transform.Scale = Vector3(0.5f);
    }

    //as long as the game is not over
    while (!bIsGameOver) {
        //make sure we process the user input
        ProcessInput();

        //apply logic based on the inputs and game logic
        Update();

        //render the screen based on the functions above
        Draw();
    }

    CloseGame();
}

void Game::ProcessInput()
{
    //run the input detection for our game input
    GameInput->ProcessInput();
}

void Game::Update()
{
    //Set delta time first always
    static double LastFrameTime = 0.0;
    //Set the current time since the game has passed
    double CurrentFrameTime = static_cast<double>(SDL_GetTicks64());
    //find the time difference between last and current frame
    double NewDeltaTime = CurrentFrameTime - LastFrameTime;
    //set delta time as seconds
    DeltaTime = NewDeltaTime / 1000.0;
    //update the last frame tiem for the next update
    LastFrameTime = CurrentFrameTime;


    //TODO:Handle Logic
    Poly->Transform.Rotation.z += 50.0f * GetFDeltaTime();
    Poly->Transform.Rotation.x += 50.0f * GetFDeltaTime();
    Poly->Transform.Rotation.y += 50.0f * GetFDeltaTime();
    
    Poly2->Transform.Rotation.z -= 50.0f * GetFDeltaTime();
    Poly2->Transform.Rotation.x -= 50.0f * GetFDeltaTime();
    Poly2->Transform.Rotation.y -= 50.0f * GetFDeltaTime();
    
    Vector3 CameraInput = Vector3(0.0f);
    Vector3 CameraRotate = Vector3(0.0f);

    CDirections CamDirection = Graphics->EngineDefaultCam->GetDirections();
    
    //move camera foward
    if (GameInput->IsKeyDown(SDL_SCANCODE_W)) {
        CameraInput += CamDirection.Forward;
    }
    //move camera backward
    if (GameInput->IsKeyDown(SDL_SCANCODE_S)) {
        CameraInput += -CamDirection.Forward;
    }
    //move camera left
    if (GameInput->IsKeyDown(SDL_SCANCODE_A)) {
        CameraInput += -CamDirection.Right;
    }
    //move camera right
    if (GameInput->IsKeyDown(SDL_SCANCODE_D)) {
        CameraInput += CamDirection.Right;
    }
    //move camera up
    if (GameInput->IsKeyDown(SDL_SCANCODE_Q)) {
        CameraInput += -CamDirection.Up;
    }
    //move camera down
    if (GameInput->IsKeyDown(SDL_SCANCODE_E)) {
        CameraInput += CamDirection.Up;
    }

    Vector3 NewLocation = Graphics->EngineDefaultCam->GetTransforms().Location += CameraInput;
    Graphics->EngineDefaultCam->Translate(NewLocation);

    //when the right mouse button is clicked, allow camera rotation
    if (GameInput->IsMouseButtonDown(MouseButtons::RIGHT)) {
        Graphics->EngineDefaultCam->RotatePitch(-GameInput->MouseYDelta * GetFDeltaTime() * 25.0f);
        Graphics->EngineDefaultCam->RotateYaw(GameInput->MouseXDelta * GetFDeltaTime() * 25.0f);
    }
    //when the middle mouse button is clicked, set the Camera FOV to default value
    if (GameInput->IsMouseButtonDown(MouseButtons::MIDDLE)) {
        Graphics->EngineDefaultCam->DefaultFOV();
        cout << "FOV set to default (70.0)" << endl;
    }
    //when mouse wheel is scrolled up, increase the FOV
    if (GameInput->ScrollDelta > 0) {
        Graphics->EngineDefaultCam->SetFOV(GameInput->ScrollDelta += 5.0f * GetFDeltaTime());
        cout << GameInput->ScrollDelta << endl;
    }
    //when mouse wheel is scrolled down, decrease the FOV
    if (GameInput->ScrollDelta < 0) {
        Graphics->EngineDefaultCam->SetFOV(GameInput->ScrollDelta -= 5.0f * GetFDeltaTime());
        cout << GameInput->ScrollDelta << endl;
    }
}

void Game::Draw()
{
    Graphics->Draw();
}

void Game::CloseGame()
{
    delete GameInput;
}
