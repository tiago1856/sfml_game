#include "ButtonEntity.h"
#include "files.h"

#include <iostream>

ButtonEntity::ButtonEntity(void (*onClick)(), ButtonState state) : AnimatedSprite{0}, onClick {onClick}
{
    setState(state);
}

ButtonEntity::~ButtonEntity()
{
}

void ButtonEntity::setState(ButtonState state)
{
    current_frame = state;
}

ButtonState ButtonEntity::getState() const
{
    return static_cast<ButtonState>(current_frame);
}

void ButtonEntity::draw(sf::RenderWindow* window)
{
    AnimatedSprite::draw(window);
}

void ButtonEntity::update(double dt)
{
    if (!bActive) return;
    if (bWait)
    {
        time += dt;
        if (time > DELTA_PRESSED_TIME)
        {
            bWait = false;
            time = 0;
            setState(current_frame == 1 ? ButtonState::DISABLED: ButtonState::HOVERED);
        }
    }
}

void ButtonEntity::event(sf::Event& event)
{
    if (event.type == sf::Event::MouseMoved && current_frame != 1)
    {
        sf::Vector2f mousePos = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
        if (current_frame == 0 && frames[current_frame]->sprite.getGlobalBounds().contains( mousePos ))
        {
            setState(ButtonState::HOVERED);
        }
        if (current_frame == 2 && !frames[current_frame]->sprite.getGlobalBounds().contains( mousePos ))
        {
            setState(ButtonState::NORMAL);
        }
    }
    else if (event.type == sf::Event::MouseButtonPressed && current_frame == 2)
    {
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            setState(ButtonState::PRESSED);
            if (onClick) onClick();
            bWait = true;
        }
    }

}

