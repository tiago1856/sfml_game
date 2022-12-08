/**
 *  Non static (animated) sprites game objects.
 *
 *  For now, frames are added individually.
 *
 *  ATT: to move/resize/... add functions to these class to iterate
 *          all through all sprites so all frames are updated correctly
 ª
 *  TODO: spritesheet to automatically create the frames.
 */

#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H


#include <memory>

#include "GameEntity.h"


class SpriteEntity;

struct Frame
{
    sf::Texture texture;
    sf::Sprite sprite;
};

class AnimatedSprite : public GameEntity
{
   public:
        AnimatedSprite(double frame_per_second);
        virtual ~AnimatedSprite();
        void addFrame(const std::string& file, const sf::Vector2f& position, const sf::Vector2f& scale);
        virtual void update(double dt);
        virtual void draw(sf::RenderWindow* window);

    protected:
        std::vector<std::shared_ptr<Frame>> frames;
        double time_progress {0.0f};
        double frame_per_second {0.0f};
        int current_frame {0};
};

#endif // ANIMATEDSPRITE_H
