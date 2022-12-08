#include "World.h"

#include <iostream>
#include <cstdlib>
#include <time.h>

#include "SpriteEntity.h"
#include "TextEntity.h"
#include "AnimatedSprite.h"
#include "BallEntity.h"
#include "ButtonEntity.h"
#include "files.h"

World::World(sf::RenderWindow* window,
             void (*onBallsOut)(),
             void (*onBallsDropped)(),
             void (*onBallWin)(),
             void (*onBallLose)(),
             void (*onButtonStart)(),
             void (*onButtonResume)(),
             void (*onButtonCreditsIn)(),
             void (*onButtonCreditsOut)(),
             void (*onBallPyramid)()
            )
    : window{window}, onBallsOut{onBallsOut}, onBallsDropped(onBallsDropped),
    onBallWin(onBallWin), onBallLose(onBallLose),
    onButtonStart(onButtonStart),onButtonResume(onButtonResume),
    onButtonCreditsIn(onButtonCreditsIn),onButtonCreditsOut(onButtonCreditsOut),
    onBallPyramid{onBallPyramid}
{
    srand(time(0));
    font = World::LoadFont(PRIMARY_FONT_FILE);
}
World::~World()
{
    clear();
}

sf::Font World::LoadFont(const std::string& filename)
{
    sf::Font font;
    if (!font.loadFromFile(filename))
    {
        std::cout << "Error: Error loading font from file [" << filename << "]" << std::endl;
    }
    return font;
}

void World::populateWorld()
{

    // STATIC SPRITES
    // the background will not be added to the entities collection
    background = std::make_shared<SpriteEntity>();
    std::shared_ptr<SpriteEntity> win_cup = std::make_shared<SpriteEntity>();
    std::shared_ptr<SpriteEntity> lose_cup = std::make_shared<SpriteEntity>();
    std::shared_ptr<SpriteEntity> pipe = std::make_shared<SpriteEntity>();
    background->load(BACKGROUND_FILE, CENTER_SCREEN );
    win_cup->load(WIN_CUP_FILE, sf::Vector2f(395.0f, 422.0f), sf::Vector2f(0.75f, 0.75f));
    lose_cup->load(LOSE_CUP_FILE, sf::Vector2f(100.0f, 422.0f), sf::Vector2f(0.75f, 0.75f));
    pipe->load(PIPE_FILE, sf::Vector2f(250.0f, 0), sf::Vector2f(0.5f, 0.5f));


    // ANIMATED SPRITES
    std::shared_ptr<AnimatedSprite> anim_triangle = std::make_shared<AnimatedSprite>(0.3f);
    anim_triangle->addFrame(TRIANGLE_FRAME_1_FILE, sf::Vector2f(250.0f, 250.0f), sf::Vector2f(0.5f, 0.5f));
    anim_triangle->addFrame(TRIANGLE_FRAME_2_FILE, sf::Vector2f(250.0f, 250.0f), sf::Vector2f(0.5f, 0.5f));


    // TEXT
    std::shared_ptr<TextEntity> credits_in_label = std::make_shared<TextEntity>(font, sf::Vector2f(30.0f, 480.0f));
    std::shared_ptr<TextEntity> credits_out_label = std::make_shared<TextEntity>(font, sf::Vector2f(180.0f, 480.0f));
    std::shared_ptr<TextEntity> plays_label = std::make_shared<TextEntity>(font, sf::Vector2f(330.0f, 480.0f));

    credits_in_value = std::make_shared<TextEntity>(font, sf::Vector2f(70.0f, 500.0f));
    credits_out_value = std::make_shared<TextEntity>(font, sf::Vector2f(220.0f, 500.0f));
    plays_value = std::make_shared<TextEntity>(font, sf::Vector2f(390.0f, 500.0f));
    balls_left = std::make_shared<TextEntity>(font, sf::Vector2f(210.0f, 390.0f));
    balls_win = std::make_shared<TextEntity>(font, sf::Vector2f(425.0f, 300.0f));
    balls_lose = std::make_shared<TextEntity>(font, sf::Vector2f(50.0f, 300.0f));

    credits_in_label->setText("CREDITS IN");
    credits_out_label->setText("CREDITS OUT");
    plays_label->setText("NUMBER OF PLAYS");


    credits_in_label->getText().setCharacterSize(16);
    credits_out_label->getText().setCharacterSize(16);
    plays_label->getText().setCharacterSize(16);
    credits_in_value->getText().setCharacterSize(14);
    credits_out_value->getText().setCharacterSize(14);
    plays_value->getText().setCharacterSize(14);
    balls_left->getText().setCharacterSize(64);
    balls_win->getText().setCharacterSize(48);
    balls_lose->getText().setCharacterSize(48);

    balls_left->getText().setFillColor(sf::Color::White);
    balls_win->getText().setFillColor(sf::Color::Blue);
    balls_lose->getText().setFillColor(sf::Color::Red);

    // buttons
    btn_start = std::make_shared<ButtonEntity>(onButtonStart, ButtonState::DISABLED);
    btn_start->addFrame(BTN_START_NORMAL, sf::Vector2f(100.0f, 600.0f), sf::Vector2f(0.35f, 0.35f));
    btn_start->addFrame(BTN_START_DISABLED, sf::Vector2f(100.0f, 600.0f), sf::Vector2f(0.35f, 0.35f));
    btn_start->addFrame(BTN_START_HOVERED, sf::Vector2f(100.0f, 600.0f), sf::Vector2f(0.35f, 0.35f));
    btn_start->addFrame(BTN_START_PRESSED, sf::Vector2f(100.0f, 600.0f), sf::Vector2f(0.35f, 0.35f));


    btn_resume = std::make_shared<ButtonEntity>(onButtonResume);
    btn_resume->setVisible(false);
    btn_resume->setActive(false);
    btn_resume->addFrame(BTN_RESUME_NORMAL, sf::Vector2f(100.0f, 600.0f), sf::Vector2f(0.35f, 0.35f));
    btn_resume->addFrame(BTN_RESUME_DISABLED, sf::Vector2f(100.0f, 600.0f), sf::Vector2f(0.35f, 0.35f));
    btn_resume->addFrame(BTN_RESUME_HOVERED, sf::Vector2f(100.0f, 600.0f), sf::Vector2f(0.35f, 0.35f));
    btn_resume->addFrame(BTN_RESUME_PRESSED, sf::Vector2f(100.0f, 600.0f), sf::Vector2f(0.35f, 0.35f));

    btn_credits_in = std::make_shared<ButtonEntity>(onButtonCreditsIn);
    btn_credits_in->addFrame(BTN_IN_NORMAL, sf::Vector2f(250.0f, 600.0f), sf::Vector2f(0.35f, 0.35f));
    btn_credits_in->addFrame(BTN_IN_DISABLED, sf::Vector2f(250.0f, 600.0f), sf::Vector2f(0.35f, 0.35f));
    btn_credits_in->addFrame(BTN_IN_HOVERED, sf::Vector2f(250.0f, 600.0f), sf::Vector2f(0.35f, 0.35f));
    btn_credits_in->addFrame(BTN_IN_PRESSED, sf::Vector2f(250.0f, 600.0f), sf::Vector2f(0.35f, 0.35f));

    btn_credits_out = std::make_shared<ButtonEntity>(onButtonCreditsOut, ButtonState::DISABLED);
    btn_credits_out->addFrame(BTN_OUT_NORMAL, sf::Vector2f(400.0f, 600.0f), sf::Vector2f(0.35f, 0.35f));
    btn_credits_out->addFrame(BTN_OUT_DISABLED, sf::Vector2f(400.0f, 600.0f), sf::Vector2f(0.35f, 0.35f));
    btn_credits_out->addFrame(BTN_OUT_HOVERED, sf::Vector2f(400.0f, 600.0f), sf::Vector2f(0.35f, 0.35f));
    btn_credits_out->addFrame(BTN_OUT_PRESSED, sf::Vector2f(400.0f, 600.0f), sf::Vector2f(0.35f, 0.35f));


    // adding to the world
    // added order relates with z-order
    add(pipe);
    add(anim_triangle);
    add(win_cup);
    add(lose_cup);

    add(credits_in_label);
    add(credits_out_label);
    add(plays_label);
    add(credits_in_value);
    add(credits_out_value);
    add(plays_value);
    add(balls_left);
    add(balls_win);
    add(balls_lose);

    buttons.push_back(btn_start);
    buttons.push_back(btn_resume);
    buttons.push_back(btn_credits_in);
    buttons.push_back(btn_credits_out);

    // balls - they will be held in a different container
    for (int i=0; i<TOTAL_BALLS; i++)
    {
        balls.push_back(std::make_shared<BallEntity>("assets/sprites/ball.png", onBallWin, onBallLose, onBallPyramid));
    }

}


void World::setCreditsIn(int credits)
{
    credits_in_value->setText(std::to_string(credits));
}

void World::setCreditsOut(int credits)
{
    credits_out_value->setText(std::to_string(credits));
}

void World::setPlays(int n_plays)
{
    plays_value->setText(std::to_string(n_plays));
}

void World::setBallsLeft(int n_balls)
{
    balls_left->setText(std::to_string(n_balls));
}

void World::setBallsWin(int n_balls)
{
    balls_win->setText(std::to_string(n_balls));
}

void World::setBallsLose(int n_balls)
{
    balls_lose->setText(std::to_string(n_balls));
}

void World::reset()
{
    current_ball = 0;
    currentTime = 0;
    bStarted = false;
    bPaused = false;
    bOutOfBalls = false;
}

void World::start()
{
    bStarted = true;
    bPaused = false;
}
void World::pause()
{
    bPaused = true;
}
void World::resume()
{
    bPaused = false;
}

void World::add(std::shared_ptr<GameEntity> ent)
{
    entities.push_back(ent);
}

void World::dropBall()
{
    if (bOutOfBalls) return;
    balls[current_ball]->activate();
    onBallsDropped();
    current_ball++;
    if (current_ball >= balls.size())
    {
        bOutOfBalls = true;
        onBallsOut();
    }
}

bool World::isPaused() const
{
    return bPaused;
}


bool World::isStarted() const
{
    return bStarted;
}

void World::update(double dt)
{
    for (auto button : buttons)
    {
        button->update(dt);
    }

    if (!bStarted || bPaused) return;

    for (auto ball : balls)
    {
        ball->update(dt);
    }

    for (auto ent : entities)
    {
        ent->update(dt);
    }

    currentTime += dt;
    if (currentTime > DELTA_BALLS)
    {
        currentTime = 0;
        dropBall();
    }
}

void World::event(sf::Event& e)
{
    for (auto button : buttons)
    {
        button->event(e);
    }
}

void World::draw()
{
    background->draw(window);

    for (auto ball : balls)
    {
        ball->draw(window);
    }

    for (auto ent : entities)
    {
        ent->draw(window);
    }

    for (auto button : buttons)
    {
        button->draw(window);
    }

}
void World::clear()
{
    std::cout << "Cleaning world." << std::endl;
    std::cout << "Deleting: "<< entities.size() + balls.size() + buttons.size() << " entities." << std::endl;

    entities.resize(0);
    balls.resize(0);
    buttons.resize(0);

    std::cout << "World clear!" << std::endl;
}

void World::setStateStartButton(ButtonState state)
{
    btn_start->setState(state);
}

void World::setStateCreditsInButton(ButtonState state)
{
    btn_credits_in->setState(state);
}

void World::setStateCreditsOutButton(ButtonState state)
{
    btn_credits_out->setState(state);
}

void World::setStatePauseButton(ButtonState state)
{
    btn_resume->setState(state);
}

void World::setDisplayPauseButton(bool display)
{
    btn_resume->setVisible(display);
    btn_resume->setActive(display);
    btn_start->setVisible(!display);
    btn_start->setActive(!display);
}

void World::loadSounds()
{
    if (!btn_buffer.loadFromFile(SOUND_BUTTON))
    {
        std::cout << "Error: Error loading sound from file [" << SOUND_BUTTON << "]" << std::endl;
    }
    if (!win_buffer.loadFromFile(SOUND_BALL_WIN))
    {
        std::cout << "Error: Error loading sound from file [" << SOUND_BALL_WIN << "]" << std::endl;
    }
    if (!lose_buffer.loadFromFile(SOUND_BALL_LOSE))
    {
        std::cout << "Error: Error loading sound from file [" << SOUND_BALL_LOSE << "]" << std::endl;
    }
    if (!victory_buffer.loadFromFile(SOUND_VICTORY))
    {
        std::cout << "Error: Error loading sound from file [" << SOUND_VICTORY << "]" << std::endl;
    }
    if (!defeat_buffer.loadFromFile(SOUND_DEFEAT))
    {
        std::cout << "Error: Error loading sound from file [" << SOUND_DEFEAT << "]" << std::endl;
    }
    if (!hit_buffer.loadFromFile(SOUND_HIT))
    {
        std::cout << "Error: Error loading sound from file [" << SOUND_HIT << "]" << std::endl;
    }
    if (!music.openFromFile(SOUND_MUSIC))
    {
        std::cout << "Error: Error loading sound from file [" << SOUND_MUSIC << "]" << std::endl;
    }
    music.setLoop(true);

    btn_sound.setBuffer(btn_buffer);
    win_sound.setBuffer(win_buffer);
    lose_sound.setBuffer(lose_buffer);
    victory_sound.setBuffer(victory_buffer);
    defeat_sound.setBuffer(defeat_buffer);
    hit_sound.setBuffer(hit_buffer);

    btn_sound.setVolume(50.0f);
    win_sound.setVolume(50.0f);
    lose_sound.setVolume(50.0f);
    victory_sound.setVolume(50.0f);
    defeat_sound.setVolume(50.0f);
    hit_sound.setVolume(50.0f);
    music.setVolume(20.0f);
}

void World::playSound(Sound sound)
{
    switch (sound)
    {
        case Sound::Button:
            btn_sound.play();
            break;
        case Sound::Defeat:
            defeat_sound.play();
            break;
        case Sound::Hit:
            hit_sound.play();
            break;
        case Sound::Lose:
            lose_sound.play();
            break;
        case Sound::Music:
            music.play();
            break;
        case Sound::Victory:
            victory_sound.play();
            break;
        case Sound::Win:
            win_sound.play();
            break;
        default:
            break;
    }
}


