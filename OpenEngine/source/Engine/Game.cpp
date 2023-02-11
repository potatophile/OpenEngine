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
    cout << "Game Destroyed" << endl;
}

void Game::Start(const char* WTitle, bool bFullscreen, int WWidth, int WHeight)
{
    //Load the window using graphics class
    Graphics = new GraphicsEngine();

    //if the window fails to load then bIsGameOver = true
    if (!Graphics->InitGE(WTitle, bFullscreen, WWidth, WHeight)) {
        bIsGameOver = true;
    }

    Run();
}

void Game::Run()
{
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
    SDL_Event event;

    //while the loop is waiting for next event
    while (SDL_PollEvent(&event)) {
        //quit the game is 'ESC' key is pressed
        if (event.key.keysym.sym == SDLK_ESCAPE) {
            exit(10);
        }
    }
}

void Game::Update()
{
}

void Game::Draw()
{
}

void Game::CloseGame()
{
}
