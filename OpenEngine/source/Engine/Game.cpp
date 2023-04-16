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

        /*//create models
        Poly = Graphics->ImportModel("Game/Models/Primitives/Cube.fbx", TextureShader);
        Poly2 = Graphics->ImportModel("Game/Models/Primitives/Sphere.fbx", TextureShader);
        
        //set the materials of the models
        Poly->SetMaterialBySlot(0, MBlueTiles);
        Poly2->SetMaterialBySlot(0, MGreenMosaic);
        
        //initial transformations for the meshes
        Poly->Transform.Location = Vector3(0.0f, 0.0f, -1.0f);
        Poly2->Transform.Location = Vector3(0.0f, 0.0f, 1.0f);*/

        //import custom meshes
        Wall = Graphics->ImportModel("Game/Models/damaged-wall/source/SM_Wall_Damaged.obj", TextureShader);
        Gundam = Graphics->ImportModel("Game/Models/Gundam/source/model.fbx", TextureShader);
        Knife = Graphics->ImportModel("Game/Models/throwing-knife-black/source/knife.fbx", TextureShader);

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
        if (Gundam != nullptr) {
            Gundam->Transform.Rotation.x = -90.0f;
            Gundam->Transform.Rotation.z = -90.0f;
            Gundam->Transform.Location = Vector3(0.0f, 0.5f, 0.0f);

            //transform the wall


            //create the texture
            TexturePtr TGundam = Graphics->CreateTexture("Game/Models/Gundam/textures/EXA-ON.png");
            TexturePtr EGundam = Graphics->CreateTexture("Game/Models/Gundam/textures/EXA-ON-E.png");
            TexturePtr SGundam = Graphics->CreateTexture("Game/Models/Gundam/textures/EXA-ON-AO.png");

            //create a material
            MaterialPtr MGundam = make_shared<Material>();
            MGundam->BaseColour.TextureV3 = TGundam;
            MGundam->EmissiveColour.TextureV3 = EGundam;
            MGundam->SpecularColour.TextureV3 = SGundam;

            //apply the material
            Gundam->SetMaterialBySlot(0, MGundam);
            Gundam->GetMaterialBySlot(0)->SpecularColour.MultiplierV3 = Vector3(1.0f);
            Gundam->GetMaterialBySlot(0)->EmissiveColour.MultiplierV3 = Vector3(1.0f);
        }
        if (Knife != nullptr) {
            //transform the wall
            Knife->Transform.Scale = Vector3(0.05f);
            Knife->Transform.Rotation.y = 90.0f;
            Knife->Transform.Location = Vector3(1.0f, 0.0f, 0.0f);

            //create the texture
            TexturePtr TKnife = Graphics->CreateTexture("Game/Models/throwing-knife-black/textures/knife_diffuseOriginal.png");

            //create a material
            MaterialPtr MKnife = make_shared<Material>();
            MKnife->BaseColour.TextureV3 = TKnife;

            //apply the material
            Knife->SetMaterialBySlot(0, MKnife);
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
    static int AnimVal = 1.0f;
    static int Rotate = 0.0f;
    
    if (Knife->Transform.Location.z > 4.5f)
        AnimVal = -1.0f;

    if (Knife->Transform.Location.z < -4.5f)
        AnimVal = 1.0f;

    if (Gundam->Transform.Location.x == 1.0f)
        Rotate = 180.0f;
    else
        Rotate = -270.0f;

    Wall->Transform.Scale += (0.01f * AnimVal) * GetFDeltaTime();

    Gundam->Transform.Location.x += (0.5f * AnimVal) * GetFDeltaTime();

    Gundam->Transform.Rotation.z = (Rotate * AnimVal);

    Knife->Transform.Rotation.z += 500.0f * AnimVal * GetFDeltaTime();
    
    Knife->Transform.Location.z += (2.0f * AnimVal) * GetFDeltaTime();
    
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
