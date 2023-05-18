#include <iostream>
#include "MenuState.h"
#include "Game.h"
#include "MenuButton.h"

const std::string MenuState::m_menuId = "MENU";

void MenuState::Update()
{
    for (auto obj : m_gameObjects) {
        obj->Update();
    }
}

void MenuState::Render()
{
    for (auto obj : m_gameObjects) {
        obj->Draw();
    }
}

bool MenuState::OnEnter()
{
    if (!TheTextureManager::Instance()->Load(
        "assets/button.png",
        "playbutton",
        TheGame::Instance()->GetRenderer())) {

        return false;
    }

    if (!TheTextureManager::Instance()->Load(
        "assets/exit.png",
        "exitbutton",
        TheGame::Instance()->GetRenderer())) {

        return false;
    }

    GameObject* playButton = new MenuButton(
        *(new LoaderParams(100, 100, 400, 100, "playbutton")));
    GameObject* exitButton = new MenuButton(
        *(new LoaderParams(100, 300, 400, 100, "exitbutton")));

    m_gameObjects.push_back(playButton);
    m_gameObjects.push_back(exitButton);

    std::cout << "Entering MenuState" << std::endl;
    return true;
}

bool MenuState::OnExit()
{
    for (auto gameObj : m_gameObjects) {
        gameObj->Clean();
    }
    m_gameObjects.clear();
    TheTextureManager::Instance()->ClearFromTextureMap("playbutton");
    TheTextureManager::Instance()->ClearFromTextureMap("exitbutton");

    std::cout << "Exiting MenuState" << std::endl;
    return true;

}