/**
 *  Simple entity to display text.
 *
 */


#ifndef TEXTENTITY_H
#define TEXTENTITY_H

#include "GameEntity.h"


class TextEntity : public GameEntity
{
    public:
        TextEntity(const sf::Font& font, const sf::Vector2f& position = sf::Vector2f(.0f, .0f));
        virtual ~TextEntity();

        void setText(const std::string& msg);
        sf::Text& getText();

        void draw(sf::RenderWindow* window) final;
        void update(double dt) final;

    private:
        sf::Text text;
};

#endif // TEXTENTITY_H
