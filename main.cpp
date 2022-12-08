/**
 *  The main, setups and controls the World.
 *  It contains the game loop and game logic, including
 *  input handling.
 *
 *  The names of the functions are self-explanatory.
 *
 */

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include <iostream>


#include "constants.h"
#include "World.h"

// forward declaration of all callbacks to be passed to the
// world.
void onBallDropped();
void onBallsOut();
void onBallWin();
void onBallLose();
void onStart();
void onCreditsIn();
void onCreditsOut();
void onResume();
void onBallPyramid();

// gameplay values
int n_credits_in {0};
int n_credits_out {INITIAL_CREDITS};  // starts with 5 credits to bet
int n_plays {0};
int n_balls_left {TOTAL_BALLS};
int n_balls_win {0};
int n_balls_lose {0};

bool out_of_balls {false};

// create the rendering window
sf::RenderWindow window(sf::VideoMode(SCREEN_X, SCREEN_Y), "Do you feel lucky, punk?");


// create world
World world(&window, onBallsOut, onBallDropped, onBallWin, onBallLose,
            onStart, onResume, onCreditsIn, onCreditsOut, onBallPyramid);




void onBallsOut()
{
    out_of_balls = true;
}

void onBallDropped()
{
    n_balls_left--;
    world.setBallsLeft(n_balls_left);
}

// new game
void reset()
{
    n_balls_left = TOTAL_BALLS;
    n_balls_win = 0;
    n_balls_lose = 0;
    out_of_balls = false;
    world.setBallsLeft(n_balls_left);
    world.setBallsWin(n_balls_win);
    world.setBallsLose(n_balls_lose);
}

void checkWin()
{
    //n_balls_left--;
    //world.setBallsLeft(n_balls_left);
    if (n_balls_win + n_balls_lose < TOTAL_BALLS) return;
    if (n_balls_win >= n_balls_lose)
    {
        std::cout << "****** WIN ********" << std::endl;
        n_credits_in += 5;
        world.setCreditsIn(n_credits_in);
        world.playSound(Sound::Victory);
    }
    else
    {
        std::cout << "****** LOSE ********" << std::endl;
        world.playSound(Sound::Defeat);
    }
    world.setStateCreditsOutButton(ButtonState::NORMAL);
    world.setStateStartButton(ButtonState::NORMAL);
    n_plays++;
    world.setPlays(n_plays);
    world.reset();
    reset();
}

void onBallWin()
{
    n_balls_win++;
    world.setBallsWin(n_balls_win);
    checkWin();
    world.playSound(Sound::Win);
}


void onBallLose()
{
    n_balls_lose++;
    world.setBallsLose(n_balls_lose);
    checkWin();
    world.playSound(Sound::Lose);
}

void onStart()
{
    world.playSound(Sound::Button);
    if (world.isStarted())
    {
        if (world.isPaused())
        {
            world.resume();
        }
        else
        {
            world.pause();
        }
    }
    else
    {
        world.start();
        n_credits_in--;
        world.setCreditsIn(n_credits_in);
        world.setStateCreditsOutButton(ButtonState::DISABLED);
    }
}

void onResume()
{
}

void onCreditsIn()
{
    world.playSound(Sound::Button);
    if (n_credits_out <= 0) return;
    n_credits_out--;
    n_credits_in++;
    world.setCreditsIn(n_credits_in);
    world.setCreditsOut(n_credits_out);
    if (!world.isStarted())
    {
        world.setStateCreditsOutButton(ButtonState::NORMAL);
    }
    world.setStateStartButton(ButtonState::NORMAL);
    if (n_credits_out <= 0)
    {
        world.setStateCreditsInButton(ButtonState::DISABLED);
    }
}

void onCreditsOut()
{
    world.playSound(Sound::Button);
    n_credits_out += n_credits_in;
    n_credits_in = 0;
    world.setStateStartButton(ButtonState::DISABLED);
    world.setCreditsIn(n_credits_in);
    world.setCreditsOut(n_credits_out);
    world.setStateCreditsInButton(ButtonState::NORMAL);
    //world.setStateCreditsOutButton(ButtonState::NORMAL);
}

void onBallPyramid()
{
    world.playSound(Sound::Hit);
}

int main()
{
    // single key input
    window.setKeyRepeatEnabled(false);

    // setup the world
    world.populateWorld();
    world.loadSounds();
    world.reset();
    world.setCreditsIn(n_credits_in);
    world.setCreditsOut(n_credits_out);
    world.setPlays(n_plays);
    world.setBallsLeft(n_balls_left);
    world.setBallsWin(n_balls_win);
    world.setBallsLose(n_balls_lose);

    // play the background music (loop - set in World)
    world.playSound(Sound::Music);


    // used to get the time per frame
    sf::Clock deltaClock;

    // game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    std::cout << "key pressed " << std::endl;
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Escape:
                            window.close();
                            break;
                        default:
                            break;
                    }
                    break;
                /*
                case sf::Event::LostFocus:
                    std::cout << "lost focus - pause game" << std::endl;
                    break;

                case sf::Event::GainedFocus:
                    std::cout << "gain focus - resume game" << std::endl;
                    break;
                */

                default:
                    break;
            }
            // pass on the event to all GameEntity that
            // needs them. Right now, only ButtonEntity
            // requires it.
            world.event(event);
        }


        window.clear();
        sf::Time dt = deltaClock.restart();
        world.update(dt.asSeconds());
        world.draw();

        window.display();
    }
    return 0;
}

