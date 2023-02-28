#pragma once
#include "Engine/Graphics/GraphicsEngine.h"
#include "CoreMinimal.h"

class Game {
public:
	//Get game instance or create if it doesn't exist
	static Game& GetGameInstance();

	//Destroy the game runnning destructor
	static void DestroyGameInstance();

	//starts the game
	//loading the window
	void Start(const char* WTitle, bool bFullscreen, int WWidth, int WHeight);

private:
	Game();
	~Game();

	//run the game loop
	void Run();

	//handle I/O
	void ProcessInput();

	//handle game logic
	void Update();

	//handle the 3D rendering
	//will clear and present each frame
	void Draw();
	
	//handle anything that needs to be deleted when the game ends
	void CloseGame();

private:
	//boolean that ends the game
	bool bIsGameOver;

	//shared pointer to the graphics class
	GraphicsEnginePtr Graphics;
};