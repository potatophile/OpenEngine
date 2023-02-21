#include "Engine/Game.h"

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
    //
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
        Graphics->CreateShader({
            L"Game/Shader/SimpleShader/SimpleShader.svert",
            L"Game/Shader/SimpleShader/SimpleShader.sfrag"
            });
        //create a triangle
        Graphics->CreateVAO(GeometricShapes::Polygon);
        Graphics->CreateVAO(GeometricShapes::Triangle);
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
}

void Game::Draw()
{
    Graphics->Draw();
}

void Game::CloseGame()
{
}
