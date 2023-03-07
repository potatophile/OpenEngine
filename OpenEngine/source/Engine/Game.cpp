#include "Engine/Game.h"
#include "Engine/Graphics/Mesh.h"

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
        //create a shader
        ShaderPtr TextureShader = Graphics->CreateShader({
            L"Game/Shader/TextureShader/TextureShader.svert",
            L"Game/Shader/TextureShader/TextureShader.sfrag"
            });
        
        //create textures
        TexturePtr TBlueTiles = Graphics->CreateTexture("Game/Textures/BlueTiles.jpg");
        TexturePtr TGreenMosaic = Graphics->CreateTexture("Game/Textures/GreenMosaic.jpg");

        //create meshes
        Poly = Graphics->CreateSimpleMeshShape(GeometricShapes::Polygon, TextureShader, { TBlueTiles });
        Tri = Graphics->CreateSimpleMeshShape(GeometricShapes::Triangle, TextureShader, { TGreenMosaic });

        //initial transformations for the meshes
        Poly->Transform.Location.x = 0.5f;
        Tri->Transform.Location.x = -0.5f;

        //Poly->Transform.Rotation.z = 45.0f;

        Poly->Transform.Scale = Vector3(0.5f);
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
    //creating event for game loop to close when a key is pressed
    SDL_Event PollEvent;

    //while the loop is waiting for input
    while (SDL_PollEvent(&PollEvent)) {
        //checking what input was pressed
        switch (PollEvent.type) {
        case SDL_QUIT:      //close button clicked
            bIsGameOver = true;
            break;
        default:
            break;
        }
    }
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

    static int MoveUp = 1.0f;

    if (Tri->Transform.Location.y > 0.5f) {
        MoveUp = -1.0f;
    }
    
    if (Tri->Transform.Location.y < -0.5f) {
        MoveUp = 1.0f;
    }

    Tri->Transform.Location.y += (1.0f * MoveUp) * GetFDeltaTime();
}

void Game::Draw()
{
    Graphics->Draw();
}

void Game::CloseGame()
{
}
