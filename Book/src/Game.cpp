#include "Game.h"
#include "TextureManager.h"
#include "Player.h"
#include "Enemy.h"
#include "InputHandler.h"
#include "MenuState.h"
#include "PlayerState.h"

Game* Game::m_instance = nullptr;

Game* Game::Instance()
{
    if (!m_instance)
    {
        m_instance = new Game;
    }
    return m_instance;
}

Game::~Game()
{
    delete renderer;
    delete window;
}

bool Game::Init(const char* title, int xPos, int yPos, int width, int height, int flags)
{
    // Init SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "SDL was initialized successfuly!" << std::endl;

        window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);

        if (window) {
            renderer = SDL_CreateRenderer(window, -1, 0);

            if (renderer) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
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

    /*if (!TheTextureManager::Instance()->Load("assets/animate-alpha.png", "animate", *renderer)) {
        return false;
    }*/

    TheInputHandler::Instance()->InitializedJoysticks();

    /*GameObject* player = new Player;
    player->Load(*(new LoaderParams(100, 100, 128, 82, "animate", 5)));
    m_gameObjects.push_back(player);

    GameObject* enemy = new Enemy;
    enemy->Load(*(new LoaderParams(300, 300, 128, 82, "animate", 5)));
    m_gameObjects.push_back(enemy);*/

    m_gameStateMachine = new GameStateMachine();
    m_gameStateMachine->ChangeState(new MenuState());

    is_running = true;

    return true;
}

void Game::HandleEvents() {
    TheInputHandler::Instance()->Update();

    if (TheInputHandler::Instance()->isKeyPressed(SDL_SCANCODE_RETURN)) {
        m_gameStateMachine->ChangeState(new PlayerState());
    }
}

void Game::Update() {
    m_gameStateMachine->Update();
}

void Game::Render() {
    SDL_RenderClear(renderer);

    m_gameStateMachine->Render();

    SDL_RenderPresent(renderer);
}

void Game::Clean() {
    TheInputHandler::Instance()->Clean();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}