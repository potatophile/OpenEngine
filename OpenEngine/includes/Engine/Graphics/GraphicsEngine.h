#pragma once

#include "SDL2/SDL.h"
#include "Engine/CoreMinimal.h"
#include "Engine/Math/Transformations.h"

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

	//create a new mesh with material assigned
	ModelPtr CreateSimpleModelShape(GeometricShapes Shape, ShaderPtr MeshShader);

	//import a 3D model based on a file path
	ModelPtr ImportModel(const char* FilePath, ShaderPtr Shader);

	//add new shader
	//@param 1 - Vertex Shader
	//@param 2 - Fragment Shader
	ShaderPtr CreateShader(VFShaderParams ShaderFilePaths);

	//create a texture and add it to the texture stack
	//avoid duplicates
	TexturePtr CreateTexture(const char* FilePath);

	//create the 3D space for the model to relate itself to
	//screen and camera coordinates
	void ApplyScreenTransformations(ShaderPtr Shader);

private:
	//this will hold the window
	SDL_Window* SdlWindow;
	//this will allow openGL to work in sdl
	SDL_GLContext SdlGLContext;
	//handle wireframe mode
	void HandleWireframeMode(bool bShowWireframeMode);
	//set wireframe
	bool bWireframeMode;

	//single shader
	ShaderPtr Shader;
	//store a vector of textures
	TexturePtrStack TextureStack;
	//store all models in the game
	ModelPtrStack ModelStack;

public:
	//default camera
	CameraPtr EngineDefaultCam;

	//default texture
	TexturePtr DefaultEngineTexture;

	//default material
	MaterialPtr DefaultEngineMaterial;
};