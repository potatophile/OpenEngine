#pragma once
#include "CoreMinimal.h"

class Input;

class Game {
public:
	//Get game instance or create if it doesn't exist
	static Game& GetGameInstance();

	//Destroy the game runnning destructor
	static void DestroyGameInstance();

	//starts the game
	//loading the window
	void Start(const char* WTitle, bool bFullscreen, int WWidth, int WHeight);

	//get precise delta time
	double GetDeltaTime() { return DeltaTime; }

	//get less precise delta time
	float GetFDeltaTime() { return static_cast<float>(DeltaTime); }

	//return the graphics engine
	GraphicsEnginePtr GetGraphics() { return Graphics; }
	//set bIsGameOver to true
	void CloseApp() { bIsGameOver = true; }

	//return the graphics engine default texture
	TexturePtr GetDefaultEngineTexture();

	//return the graphics engine default material
	MaterialPtr GetDefaultEngineMaterial();

	//remove a model from everywhere it needs to be removed
	void RemoveModelFromGame(ModelPtr& ModelToRemove);

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

	//the time between each frame
	double DeltaTime;

	//read the input of the player
	Input* GameInput;

	//temporary model variables
	ModelPtr Ground;
	ModelPtr Car;
	
	ModelPtr LWall1;
	ModelPtr LWall2;
	ModelPtr LWall3;
	ModelPtr LWall4;
	ModelPtr LWall5;
	ModelPtr LWall6;
	ModelPtr LWall7;
	ModelPtr LWall8;
	ModelPtr LWall9;
	ModelPtr LWall10;
	ModelPtr LWall11;
	ModelPtr LWall12;
	ModelPtr LWall13;
	ModelPtr LWall14;
	ModelPtr LWall15;
	ModelPtr LWall16;
	ModelPtr LWall17;
	ModelPtr LWall18;
	ModelPtr LWall19;
	ModelPtr LWall20;
	ModelPtr LWall21;
	ModelPtr RWall1;
	ModelPtr RWall2;
	ModelPtr RWall3;
	ModelPtr RWall4;
	ModelPtr RWall5;
	ModelPtr RWall6;
	ModelPtr RWall7;
	ModelPtr RWall8;
	ModelPtr RWall9;
	ModelPtr RWall10;
	ModelPtr RWall11;
	ModelPtr RWall12;
	ModelPtr RWall13;
	ModelPtr RWall14;
	ModelPtr RWall15;
	ModelPtr RWall16;
	ModelPtr RWall17;
	ModelPtr RWall18;
	ModelPtr RWall19;
	ModelPtr RWall20;
	ModelPtr RWall21;

	ModelPtr StartWall;
	ModelPtr EndWall;
	
	ModelPtr Coin1;
	ModelPtr Coin2;
	ModelPtr Coin3;
	ModelPtr Coin4;
	ModelPtr Coin5;
	ModelPtr Coin6;
	ModelPtr Coin7;
	ModelPtr Coin8;
	ModelPtr Coin9;
	ModelPtr Coin10;
	ModelPtr Coin11;
	ModelPtr Coin12;
	ModelPtr Coin13;
	ModelPtr Coin14;
	ModelPtr Coin15;
	ModelPtr Coin16;
	ModelPtr Coin17;
	ModelPtr Coin18;

	ModelPtr Spike1;
	ModelPtr Spike2;
	ModelPtr Spike3;
	ModelPtr Spike4;
	ModelPtr Spike5;
	ModelPtr Spike6;
	ModelPtr Spike7;
	ModelPtr Spike8;
	ModelPtr Spike9;
	ModelPtr Spike10;
	ModelPtr Spike11;
	ModelPtr Spike12;
	ModelPtr Spike13;
	ModelPtr Spike14;
};