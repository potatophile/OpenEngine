#pragma once

#include "Engine/CoreMinimal.h"
#include "SDL2/SDL.h"

class GraphicsEngine {
public:
	GraphicsEngine();
	~GraphicsEngine();

	//create the window
	bool InitGE(const char* WTitle, bool bFullscreen, int WWidth, int WHeight);
	
	//show the newest frame graphics
	void PresentGraphics();
	//clear the old frame graphics
	void ClearGraphics();
	//handle the rendering of graphics
	void Draw();

	//return the sdl window
	SDL_Window* GetWindow() const;

	//add a new VAO to the VAOStack
	void CreateVAO();

private:
	//this will hold the window
	SDL_Window* SdlWindow;
	//this will allow openGL to work in sdl
	SDL_GLContext SdlGLContext;
	//stack all the VAOS
	VAOStack VAOs;
	//handle wireframe mode
	void HandleWireframeMode(bool bShowWireframeMode);
	//set wireframe
	bool bWireframeMode;
};