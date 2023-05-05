#include "Game.h"

int main(int argc, char* argv[]) {
    auto theGame = TheGame::Instance();

    theGame->Init("Chapter 1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);

    while (theGame->IsRunning()) {
        theGame->HandleEvents();
        theGame->Update();
        theGame->Render();

        SDL_Delay(10);
    }

    theGame->Clean();

    return 0;
}