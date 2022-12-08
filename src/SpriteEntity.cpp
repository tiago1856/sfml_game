#include "SpriteEntity.h"

#include <iostream>

SpriteEntity::SpriteEntity()
{
    //ctor
}

SpriteEntity::~SpriteEntity()
{
}


bool SpriteEntity::load(const std::string& file, const sf::Vector2f& position, const sf::Vector2f& scale)
{
    if ( !texture.loadFromFile( file ) )
    {
        std::cout << "Error: Could not load [" << file << "] image" << std::endl;
        return false;
    }
    sprite.setTexture( texture );

    auto size = sprite.getTexture()->getSize();

    sprite.setOrigin(sf::Vector2f(size.x * 0.5, size.y * 0.5));

    sprite.setPosition(position);
    sprite.setScale(scale);

    return true;
}


const sf::Sprite& SpriteEntity::getSprite() const
{
    return sprite;
}
/*
void SpriteEntity::setScale(float x, float y)
{
    sprite.setScale(sf::Vector2f(x, y));
}

void SpriteEntity::setPosition(float x, float y)
{
    sprite.setPosition(sf::Vector2f(x,y));
}
*/
void SpriteEntity::draw(sf::RenderWindow* window)
{
    if (!bVisible) return;
    window->draw(sprite);
}

void SpriteEntity::update(double dt)
{
    if (!bActive) return;
}
