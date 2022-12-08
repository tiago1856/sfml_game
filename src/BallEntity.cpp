#include "BallEntity.h"

#include <cstdlib>
#include <cmath>
#include <iostream>

BallEntity::BallEntity(const std::string& file,
            void (*onTargetWin)(),
            void (*onTargetLost)(),
            void (*onPyramid)(),
            const sf::Vector2f& position,
            const sf::Vector2f& scale) : onTargetWin {onTargetWin}, onTargetLost {onTargetLost}, onPyramid {onPyramid}
{
    exists = load(file, position, scale);
    bActive = false;
    bVisible = false;
}

BallEntity::~BallEntity()
{
}

void BallEntity::activate()
{
    bVisible = true;
    bActive = true;
    isOnPyramid = false;
    direction = 1;
    angle = DOWN_ANGLE;
    sprite.setPosition(START_POSITION);
}

void BallEntity::draw(sf::RenderWindow* window)
{
    SpriteEntity::draw(window);
}

void BallEntity::update(double dt)
{
    SpriteEntity::update(dt);

    if (!bActive) return;

    double x = SPEED * dt * cos(angle) * direction;
    double y = SPEED * dt * sin(angle);
    sprite.move(x,y);

    if (!isOnPyramid && sprite.getPosition().y > CHANGE_DIRECTION_Y)
    {
        isOnPyramid = true;
        angle = atan2(500,250);
        direction = rand() % 2 == 0 ? 1 : -1;
        if (onPyramid) onPyramid();
    }

    // one of the target was reached => deactivate ball and call respective
    // callback function
    if (sprite.getPosition().y > TARGET_Y)
    {
        bActive = false;
        bVisible = false;
        if (onTargetWin && onTargetLost)
        {
            direction == 1 ? onTargetWin() : onTargetLost();
        }
    }

}
