#include "Engine/Game.h"
#include "Engine/Graphics/Model.h"
#include "Engine/Graphics/GraphicsEngine.h"
#include "Engine/Input.h"
#include "Engine/Graphics/Camera.h"
#include "Engine/Graphics/Material.h"

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

TexturePtr Game::GetDefaultEngineTexture()
{
    return Graphics->DefaultEngineTexture;
}

MaterialPtr Game::GetDefaultEngineMaterial()
{
    return Graphics->DefaultEngineMaterial;
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

        //create the materials
        MaterialPtr MGreenMosaic = make_shared<Material>();
        MaterialPtr MBlueTiles = make_shared<Material>();

        //assign the base colour of the materials using the textures
        MGreenMosaic->BaseColour.TextureV3 = TGreenMosaic;
        MBlueTiles->BaseColour.TextureV3 = TBlueTiles;

        //create models
        Poly = Graphics->ImportModel("Game/Models/Primitives/Cube.fbx", TextureShader);
        Poly2 = Graphics->ImportModel("Game/Models/Primitives/Sphere.fbx", TextureShader);
        
        //set the materials of the models
        Poly->SetMaterialBySlot(0, MBlueTiles);
        Poly2->SetMaterialBySlot(0, MGreenMosaic);
        
        //initial transformations for the meshes
        Poly->Transform.Location = Vector3(0.0f, 0.0f, -1.0f);
        Poly2->Transform.Location = Vector3(0.0f, 0.0f, 1.0f);

        //import custom meshes
        Wall = Graphics->ImportModel("Game/Models/damaged-wall/source/SM_Wall_Damaged.obj", TextureShader);

        if (Wall != nullptr) {
            Wall->Transform.Scale = Vector3(0.05f);
            Wall->Transform.Rotation.y = 90.0f;
            Wall->Transform.Location = Vector3(2.0f, -2.0f, 0.0f);

            //transform the wall


            //create the texture
            TexturePtr TWall = Graphics->CreateTexture("Game/Models/damaged-wall/textures/Wall_Damaged_BC.png");

            //create a material
            MaterialPtr MWall = make_shared<Material>();
            MWall->BaseColour.TextureV3 = TWall;

            //apply the material
            Wall->SetMaterialBySlot(1, MWall);
        }
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
    
    Graphics->EngineDefaultCam->GetCameraData().FarClip;

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
    }//move camera down
    if (GameInput->IsKeyDown(SDL_SCANCODE_E)) {
        CameraInput += CamDirection.Up;
    }

    //move the camera based on input
    Graphics->EngineDefaultCam->AddMovementInput(CameraInput);

    if (GameInput->IsMouseButtonDown(MouseButtons::RIGHT)) {
        Graphics->EngineDefaultCam->RotatePitch(-GameInput->MouseYDelta * GetFDeltaTime());
        Graphics->EngineDefaultCam->RotateYaw(GameInput->MouseXDelta * GetFDeltaTime());
        GameInput->ShowCursor(false);
    }
    else {
        GameInput->ShowCursor(true);
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
