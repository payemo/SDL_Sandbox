#include "Game.h"

const int FPS = 60;
const int DELAY_TIME = 1000.f / FPS;

int main(int argc, char* argv[]) {
    Uint32 frameStart, frameTime;

    auto theGame = TheGame::Instance();

    theGame->Init("Chapter 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);

    while (theGame->IsRunning()) {
        frameStart = SDL_GetTicks();

        theGame->HandleEvents();
        theGame->Update();
        theGame->Render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameTime < DELAY_TIME) {
            SDL_Delay(static_cast<int>(DELAY_TIME - frameTime));
        }

    }

    theGame->Clean();

    return 0;
}