/**
 *  A static (not animated) sprite game object.
 *  For moving, scaling and so on, use sf::Sprite methods directly
 *  on the sprite member.
 *
 */

#ifndef SPRITEENTITY_H
#define SPRITEENTITY_H

#include "GameEntity.h"


class SpriteEntity : public GameEntity
{
    public:
        SpriteEntity();
        virtual ~SpriteEntity();

        bool load(const std::string& file, const sf::Vector2f& position = sf::Vector2f(.0f, .0f), const sf::Vector2f& scale = sf::Vector2f(1.0f, 1.0f));
        const sf::Sprite& getSprite() const;
        virtual void draw(sf::RenderWindow* window);
        virtual void update(double dt);

    protected:
        sf::Texture texture;
        sf::Sprite sprite;
};

#endif // SPRITEENTITY_H
