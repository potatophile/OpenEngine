#include "Engine/Graphics/GraphicsEngine.h"
#include "GLEW/glew.h"
#include "Engine/Graphics/VertexArrayObject.h"
#include "Engine/Graphics/ShaderProgram.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

GraphicsEngine::GraphicsEngine()
{
	SdlWindow = nullptr;
	SdlGLContext = NULL;
	bWireframeMode = false;
}

GraphicsEngine::~GraphicsEngine()
{
	cout << "Destroy Graphics Engine..." << endl;
	//this will handle deleting the sdl window from memory
	SDL_DestroyWindow(SdlWindow);
	//destroy the GL Context for sdl
	SDL_GL_DeleteContext(SdlGLContext);
	//close tthe sdl window
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

	HandleWireframeMode(false);			//wireframe mode off when false

	UNint index = 0;

	//render between these two functions
	for (VAOPtr VAO : VAOs) {
		Shader->RunShader();

		//move the object
		glm::mat4 transform = glm::mat4(1.0f);

		if (index == 0) {	//DIAMOND
			//move in the x, y or z direction based on the amount added
			transform = glm::translate(transform, glm::vec3(-0.6f, -0.6f, 0.0f));		//translate to bottom-right
			
			//radians = rotation amount
			//vec3 is the direction to rotate in
			transform = glm::rotate(transform, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0));	//rotate by 45 radians
			
			transform = glm::scale(transform, glm::vec3(0.5f, 0.5f, 1.0f));			//scale down to half size
		}
		else if(index == 1) {//TRIANGLE
			transform = glm::translate(transform, glm::vec3(-0.7f, 0.7f, 0.0f));		//Translate to top-left
			
			//x and y will work for 2D shapes
			//z must be larger than 0 to make it visible
			transform = glm::scale(transform, glm::vec3(0.5f, 0.5f , 1.0f));			//scale down to half size
		}
		else if (index == 2) {//CIRCLE
			transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.0f));			//translate to center

			transform = glm::scale(transform, glm::vec3(0.8f, 0.8f, 1.0f));				//scale down to 0.7
		}
		else if (index == 3) {//STAR
			transform = glm::translate(transform, glm::vec3(0.6f, 0.6f, 0.0f));			//translate to top-right
		}
		else if (index == 4) {//CROSS
			transform = glm::translate(transform, glm::vec3(0.6f, -0.6f, 0.0f));		//translate to bottom-left
			
			transform = glm::scale(transform, glm::vec3(0.6f, 0.6f, 1.0f));				//scale down to half size
			
			transform = glm::rotate(transform, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0));	//rotate by 45 radians
		}

		Shader->SetMat4("transform", transform);

		//Draw each VAO
		VAO->Draw();

		index++;
	}

	index = 0;

	PresentGraphics();
}

SDL_Window* GraphicsEngine::GetWindow() const
{
	return SdlWindow;
}

void GraphicsEngine::CreateVAO(GeometricShapes Shape)
{
	//create a new VAO as a shared pointer
	VAOPtr NewVAO = make_shared<VAO>(Shape);
	//Add it to the stack
	VAOs.push_back(NewVAO);
}

void GraphicsEngine::CreateShader(VFShaderParams ShaderFilePaths)
{
	//create a new shader class
	ShaderPtr NewShader = make_shared<ShaderProgram>();
	//initialize the shader into openGL using the file paths
	NewShader->InitVFShader(ShaderFilePaths);
	//add the shader to our graphics engine
	Shader = NewShader;
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
