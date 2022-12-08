/**
 *  The abstract parent class of every game object.
 *
 */

#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include <SFML/Graphics.hpp>


class GameEntity
{
    public:
        GameEntity();
        virtual ~GameEntity();

        virtual void draw(sf::RenderWindow* window) = 0;
        virtual void update(double dt) = 0;
        virtual void event(sf::Event& e) {};

        void setActive(bool active);
        void setVisible(bool visible);

    protected:
        bool bActive {true};
        bool bVisible {true};

};

#endif // GAMEENTITY_H
