#include "AnimatedSprite.h"
#include "SpriteEntity.h"

#include <iostream>

AnimatedSprite::AnimatedSprite(double frame_per_second) : frame_per_second{frame_per_second}
{
}

AnimatedSprite::~AnimatedSprite()
{
    frames.resize(0);
}

void AnimatedSprite::addFrame(const std::string& file, const sf::Vector2f& position, const sf::Vector2f& scale)
{
    std::shared_ptr<Frame> frame = std::make_shared<Frame>();
    if ( !frame->texture.loadFromFile( file ) )
    {
        std::cout << "Error: Could not display [" << file << "] image" << std::endl;
    }

    frame->sprite.setTexture( frame->texture );

    auto size = frame->sprite.getTexture()->getSize();

    frame->sprite.setOrigin(sf::Vector2f(size.x * 0.5, size.y * 0.5));

    frame->sprite.setPosition(position);
    frame->sprite.setScale(scale);
    frames.push_back(frame);
}

void AnimatedSprite::update(double dt) {
    if (!bActive) return;
    time_progress += dt;
    if (time_progress > frame_per_second)
    {
        time_progress = 0;
        current_frame ++;
        current_frame %= frames.size();
    }
}

void AnimatedSprite::draw(sf::RenderWindow* window)
{
    if (!bVisible || frames.size() == 0) return;
    window->draw(frames[current_frame]->sprite);
}
