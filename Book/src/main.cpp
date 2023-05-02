#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[]) {
	game = new Game();

	game->Init("Chapter 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);

	while (game->IsRunning()) {
		game->HandleEvents();
		game->Update();
		game->Render();
	}

	game->Clean();

	return 0;
}