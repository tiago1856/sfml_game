/**
 *  A moving SpriteEntity.
 *  The movement of each ball consists of 2 parts:
 *      - direct fall
 *      - following a slope
 *  The movement starts with the fall. Once it reaches a certain Y
 *  (tip of the triangle) it follows one the sides of the triangle.
 *  This side is randomly selected.
 *  Once the ball reaches another Y, corresponding to the targets,
 *  it stops (the ball remains inactive), until the next play.
 *
 */


#ifndef BALL_H
#define BALL_H

#include "SpriteEntity.h"
#include "constants.h"

static const double PI = 3.1415;
// behind the pipe
static const sf::Vector2f START_POSITION = sf::Vector2f(CENTER_SCREEN_X, 25);
static const sf::Vector2f SCALE = sf::Vector2f(0.15f, 0.15f);
// Y coordinate of the targets (cup or the "brown" emoji"
static const int TARGET_Y = 400;
// Y coordinate of the triangle tip
static const int CHANGE_DIRECTION_Y = 100;
static const double SPEED = 100.0f;
static const double DOWN_ANGLE = 90 * PI / 180;

class BallEntity : public SpriteEntity
{
    public:
        BallEntity(   const std::string& file,
                void (*onTargetWin)() = nullptr,
                void (*onTargetLost)() = nullptr,
                void (*onPyramid)() = nullptr,
                const sf::Vector2f& position = START_POSITION,
                const sf::Vector2f& scale = SCALE
                );
        ~BallEntity();
        void draw(sf::RenderWindow* window) final;
        void update(double dt) final;
        void activate();
    private:
        // callbacks for when ball reaches one of the targets and tip or the triangle
        void (*onTargetWin)() {nullptr};
        void (*onTargetLost)() {nullptr};
        void (*onPyramid)() {nullptr};
        bool exists {false};
        bool isOnPyramid {false};
        int direction { 1 }; // 1 => right | -1 => left
        double angle {DOWN_ANGLE};
};

#endif // BALL_H
