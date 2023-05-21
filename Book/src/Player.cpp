#include "Player.h"
#include "InputHandler.h"

Player::Player() : SDLGameObject()
{
}

void Player::Update()
{
    m_velocity.SetX(0);
    m_velocity.SetY(0);

    HandleInput();

    m_currentFrame = int(((SDL_GetTicks() / 100) % m_numFrames));

    SDLGameObject::Update();
}

void Player::HandleInput()
{
    InputHandler* ih = TheInputHandler::Instance();

    // mouse moving
    const Vector2D& vec = ih->GetMousePosition();
    m_velocity = (vec - m_position) / 50;

    if (ih->XValue(0, 1) > 0 || ih->XValue(0, 1) < 0) {
        m_velocity.SetX(ih->XValue(0, 1));
    }

    if (ih->YValue(0, 1) > 0 || ih->YValue(0, 1) < 0) {
        m_velocity.SetY(ih->YValue(0, 1));
    }

    if (ih->XValue(0, 2) > 0 || ih->XValue(0, 2) < 0) {
        m_velocity.SetX(ih->XValue(0, 2));
    }

    if (ih->YValue(0, 2) > 0 || ih->YValue(0, 2) < 0) {
        m_velocity.SetY(ih->YValue(0, 2));
    }

    if (ih->GetMouseButtonState(LEFT)) {
        m_velocity.SetX(1);
    }

    if (ih->isKeyPressed(SDL_SCANCODE_RIGHT)) {
        m_velocity.SetX(2);
    }

    if (ih->isKeyPressed(SDL_SCANCODE_LEFT)) {
        m_velocity.SetX(-2);
    }

    if (ih->isKeyPressed(SDL_SCANCODE_UP)) {
        m_velocity.SetY(-2);
    }

    if (ih->isKeyPressed(SDL_SCANCODE_DOWN)) {
        m_velocity.SetY(2);
    }
}