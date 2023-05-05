#include "Game.h"
#include "TextureManager.h"
#include "Player.h"
#include "Enemy.h"

Game* Game::m_instance = nullptr;

Game* Game::Instance()
{
    if (!m_instance)
    {
        m_instance = new Game;
    }
    return m_instance;
}

//Game::~Game() {
//    if (!window) {
//        delete window;
//    }
//
//    if (!renderer) {
//        delete renderer;
//    }
//}

bool Game::Init(const char* title, int xPos, int yPos, int width, int height, int flags)
{
    m_gameObjects.push_back(new Player(
        *(new LoaderParams(100, 100, 128, 82, "animate"))));
    m_gameObjects.push_back(new Enemy(
        *(new LoaderParams(300, 300, 128, 82, "animate"))));

    // Init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "SDL was initialized successfuly.!" << std::endl;

        window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);

        if (window) {
            renderer = SDL_CreateRenderer(window, -1, 0);

            if (renderer) {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            }
            else {
                std::cout << "SDL renderer init fails." << std::endl;
                return false;
            }
        }
        else {
            std::cout << "SDL window init fails." << std::endl;
            return false;
        }
    }
    else {
        std::cout << "SDL init fails!" << std::endl;
        return false;
    }

    if (!TheTextureManager::Instance()->Load("assets/animate-alpha.png", "animate", *renderer)) {
        return false;
    }

    is_running = true;

    return true;
}

void Game::HandleEvents() {
    SDL_Event event;

    if (SDL_PollEvent(&event)) {
        switch (event.type)
        {
        case SDL_QUIT:
            is_running = false;
            break;

        default:
            break;
        }
    }
}

void Game::Update() {
    for (auto obj : m_gameObjects) {
        obj->Update();
    }
}

void Game::Render() {
    SDL_RenderClear(renderer);

    for (auto obj : m_gameObjects) {
        obj->Draw();
    }

    SDL_RenderPresent(renderer);
}

void Game::Clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}