#include "Engine/Graphics/GraphicsEngine.h"
#include "GLEW/glew.h"
#include "Engine/Graphics/Mesh.h"
#include "Engine/Graphics/ShaderProgram.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Engine/Graphics/Texture.h"

GraphicsEngine::GraphicsEngine()
{
	SdlWindow = nullptr;
	SdlGLContext = NULL;
	bWireframeMode = false;
}

GraphicsEngine::~GraphicsEngine()
{
	//clear the mesh stack
	MeshStack.clear();

	//clear shader
	Shader = nullptr;

	//remove textures from memory
	TextureStack.clear();		//clear() empties the array/vector

	//this will handle deleting the sdl window from memory
	SDL_DestroyWindow(SdlWindow);
	//destroy the GL Context for sdl
	SDL_GL_DeleteContext(SdlGLContext);
	//close the sdl window
	SDL_Quit();

	cout << "Destroyed Graphics Engine..." << endl;
}

bool GraphicsEngine::InitGE(const char* WTitle, bool bFullscreen, int WWidth, int WHeight)
{
	//make sure sdl initialises
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cout << "SDL Failed: " << SDL_GetError() << endl;
		return false;
	}

	//Use OpenGL 4.6 compatibility and set default attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	
	//Set the fullscreen flag
	int FullscreenFlag = 0;

	if (bFullscreen) {
		FullscreenFlag = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
	}
	else {
		FullscreenFlag = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
	}

	//create the sdl2 window
	SdlWindow = SDL_CreateWindow(
		WTitle,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WWidth, WHeight,
		FullscreenFlag
	);

	//if the window fails
	if (SdlWindow == nullptr) {
		cout << "SDL Window Failed: " << SDL_GetError() << endl;
	}

	//add all the gl attributes to the window
	SdlGLContext = SDL_GL_CreateContext(SdlWindow);

	if (SdlGLContext == NULL) {
		cout << "SDL GL Context Failed: " << SDL_GetError() << endl;
		return false;
	}

	//to make glew work we need to mark experimental true
	glewExperimental = GL_TRUE;

	const GLenum InitGLEW = glewInit();

	if (InitGLEW != GLEW_OK) {
		cout << "Glew Failed: " << glewGetErrorString(InitGLEW) << endl;
		return false;
	}

	return true;
}

void GraphicsEngine::PresentGraphics()
{
	//present the new graphics using opengl
	SDL_GL_SwapWindow(SdlWindow);
}

void GraphicsEngine::ClearGraphics()
{
	//set the background color
	glClearColor(0.23f, 0.38f, 0.47f, 1.0f);

	//clear the screen
	glClear(GL_COLOR_BUFFER_BIT);
}

void GraphicsEngine::Draw()
{
	ClearGraphics();

	HandleWireframeMode(false);

	//run through each mesh and call its draw method
	for (MeshPtr LMesh : MeshStack) {
		LMesh->Draw();
	}

	PresentGraphics();
}

SDL_Window* GraphicsEngine::GetWindow() const
{
	return SdlWindow;
}

MeshPtr GraphicsEngine::CreateSimpleMeshShape(GeometricShapes Shape, ShaderPtr MeshShader, TexturePtrStack MeshTextures)
{
	//initialize a new mesh class
	MeshPtr NewMesh = make_shared<Mesh>();

	//make sure it worked
	if (!NewMesh->CreateSimpleShape(Shape, MeshShader, MeshTextures))
		return nullptr;

	//add mesh into the stack of meshses to be rendered
	MeshStack.push_back(NewMesh);

	//return the new mesh
	return NewMesh;
}

ShaderPtr GraphicsEngine::CreateShader(VFShaderParams ShaderFilePaths)
{
	//create a new shader class
	ShaderPtr NewShader = make_shared<ShaderProgram>();
	//initialize the shader into openGL using the file paths
	NewShader->InitVFShader(ShaderFilePaths);
	//add the shader to our graphics engine
	Shader = NewShader;

	return NewShader;
}

TexturePtr GraphicsEngine::CreateTexture(const char* FilePath)
{
	TexturePtr NewTexture = nullptr;
	
	//Run through all the texture and check if one with the same path exists
	for (TexturePtr TestTexture : TextureStack) {
		//if we find a texture with the same file path
		if (TestTexture->GetFilePath() == FilePath) {
			//pass in the already created texture
			NewTexture = TestTexture;
			cout << "Texture found: Assigning current texture." << endl;
			break;
		}
	}

	//if there is no texture already existing
	if (NewTexture == nullptr) {
		cout << "Creating a new texture..." << endl;

		//create a new texture as a shared ptr
		NewTexture = make_shared<Texture>();

		//if the file was found assign it to the texture stack
		if (NewTexture->CreateTextureFromFilePath(FilePath)) {
			cout << "Texture " << NewTexture->GetID() << " creation successful! Adding to Texture Stack." << endl;

			//add the texture to the texture stack
			TextureStack.push_back(NewTexture);
		}
	}

	return NewTexture;
}

void GraphicsEngine::HandleWireframeMode(bool bShowWireframeMode)
{
	// if wireframe mode is set, change it and vice versa
	if (bShowWireframeMode != bWireframeMode) {
		bWireframeMode = bShowWireframeMode;

		//change how openGL renders between vertices
		if (bWireframeMode) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		cout << "Wireframe Mode Updated..." << endl;
	}
}
