#include "GameEntity.h"

#include <iostream>

GameEntity::GameEntity()
{
    //ctor
}

GameEntity::~GameEntity()
{
}

void GameEntity::setActive(bool active)
{
    bActive = active;
}

void GameEntity::setVisible(bool visible)
{
    bVisible = visible;
}
