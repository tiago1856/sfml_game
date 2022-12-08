/**
 *  Main game class - it creates and populates the world. It also proceeds to reset
 *      the game for next play and it's also responsible to clean everything when exit.
 *
 *  Note: all sounds are loaded and played through this class, for simplicity.
 *  This option works, since there are no overlapping of the same sound.
 */

#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "constants.h"


class TextEntity;
class GameEntity;
class BallEntity;
class SpriteEntity;
class ButtonEntity;

enum Sound {Button, Win, Lose, Victory, Defeat, Music, Hit};

class World
{
    public:
        World(sf::RenderWindow* window,
              void (*onBallsOut)() = nullptr,
              void (*onBallsDropped)() = nullptr,
              void (*onBallWin)() = nullptr,
              void (*onBallLose)() = nullptr,
              void (*onButtonStart)() = nullptr,
              void (*onButtonResume)() = nullptr,
              void (*onButtonCreditsIn)() = nullptr,
              void (*onButtonCreditsOut)() = nullptr,
              void (*onBallPyramid)() = nullptr
              );
        ~World();
        static sf::Font LoadFont(const std::string& filename);
        void populateWorld();
        void add(std::shared_ptr<GameEntity> ent);
        void update(double dt);
        void draw();
        void event(sf::Event& e);
        void clear();

        void setCreditsIn(int credits);
        void setCreditsOut(int credits);
        void setPlays(int n_plays);
        void setBallsLeft(int n_balls);
        void setBallsWin(int n_balls);
        void setBallsLose(int n_balls);

        void dropBall();
        void start();
        void pause();
        void resume();
        bool isPaused() const;
        bool isStarted() const;

        void setStateStartButton(ButtonState state);
        void setStatePauseButton(ButtonState state);
        void setStateCreditsInButton(ButtonState state);
        void setStateCreditsOutButton(ButtonState state);
        void setDisplayPauseButton(bool display);

        void reset();
        void loadSounds();
        void playSound(Sound sound);

    private:
        sf::RenderWindow* window;
        std::vector<std::shared_ptr<GameEntity>> entities;  // general entities except balls and buttons
        std::vector<std::shared_ptr<BallEntity>> balls;
        std::vector<std::shared_ptr<ButtonEntity>> buttons;
        std::shared_ptr<SpriteEntity> background {nullptr};
        std::shared_ptr<ButtonEntity> btn_start {nullptr};
        std::shared_ptr<ButtonEntity> btn_resume {nullptr};
        std::shared_ptr<ButtonEntity> btn_credits_in {nullptr};
        std::shared_ptr<ButtonEntity> btn_credits_out {nullptr};

        std::shared_ptr<TextEntity> credits_in_value {nullptr};
        std::shared_ptr<TextEntity> credits_out_value {nullptr};
        std::shared_ptr<TextEntity> plays_value {nullptr};
        std::shared_ptr<TextEntity> balls_left {nullptr};
        std::shared_ptr<TextEntity> balls_win {nullptr};
        std::shared_ptr<TextEntity> balls_lose {nullptr};

        sf::Font font;
        // index of the last dropped ball
        int current_ball {0};

        void (*onBallsOut)() { nullptr };
        void (*onBallsDropped)() { nullptr };
        void (*onBallWin)() { nullptr };
        void (*onBallLose)() { nullptr };
        void (*onButtonStart)() { nullptr };
        void (*onButtonResume)() { nullptr };
        void (*onButtonCreditsIn)() { nullptr };
        void (*onButtonCreditsOut)() { nullptr };
        void (*onBallPyramid)() { nullptr };

        double currentTime {0};
        bool bStarted { false };
        bool bPaused { false };
        bool bOutOfBalls {false};

        sf::SoundBuffer btn_buffer;
        sf::SoundBuffer win_buffer;
        sf::SoundBuffer lose_buffer;
        sf::SoundBuffer victory_buffer;
        sf::SoundBuffer defeat_buffer;
        sf::SoundBuffer hit_buffer;
        sf::Music music;
        sf::Sound btn_sound;
        sf::Sound win_sound;
        sf::Sound lose_sound;
        sf::Sound victory_sound;
        sf::Sound defeat_sound;
        sf::Sound hit_sound;
};

#endif // WORLD_H
