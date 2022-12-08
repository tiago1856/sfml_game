/**
 *  An AnimatedSprite working as a Button.
 *  Each frame corresponds to one of 4 states (defined in constants.h):
 *      - NORMAL
 *      - DISABLED
 *      - HOVERED
 *      - PRESSED
 *
 *  The frames must be added in that exact order and must be 4 of them.
 *  Each frame is defined by a sprite.
 *  When mouse pressed, it calls the callback function.
 */

#ifndef BUTTONENTITY_H
#define BUTTONENTITY_H


#include "AnimatedSprite.h"
#include "constants.h"


static const double DELTA_PRESSED_TIME = 0.25f;

class ButtonEntity : public AnimatedSprite
{
    public:
        ButtonEntity(void (*onClick)() = nullptr, ButtonState state = ButtonState::NORMAL);
        ~ButtonEntity();

        void setState(ButtonState state);
        ButtonState getState() const;

        void update(double dt) final;
        void draw(sf::RenderWindow* window) final;
        void event(sf::Event& e) final;

    private:
        void (*onClick)() {nullptr};
        double time {0};
        bool bWait {false};
        //ButtonState state;
};

#endif // BUTTONENTITY_H
