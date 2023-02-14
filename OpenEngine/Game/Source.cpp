#include "Engine/Game.h"

int main(int argc, char** argv) {
	Game::GetGameInstance().Start("OpenEngine | An OpenGL Engine", false, 720,720);

	Game::DestroyGameInstance();
	return 0;
}