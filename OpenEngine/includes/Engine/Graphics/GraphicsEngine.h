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

	//add a new VAO to the VAOStack using a shape define
	void CreateVAO(GeometricShapes Shape);

	//add new shader
	//@param 1 - Vertex Shader
	//@param 2 - Fragment Shader
	void CreateShader(VFShaderParams ShaderFilePaths);

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

	//single shader
	ShaderPtr Shader;
};