/**
 * Constants and defaults.
 *
 * Note: all values are in pixels, unless otherwise explicit.
 *
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

// button frames should be inserted in the same order as the enum
enum ButtonState {NORMAL, DISABLED, HOVERED, PRESSED};

const int SCREEN_X = 500;
const int SCREEN_Y = 700;
const int CENTER_SCREEN_X = 250;
const int CENTER_SCREEN_Y = 350;
const sf::Vector2f CENTER_SCREEN = sf::Vector2f(CENTER_SCREEN_X, CENTER_SCREEN_Y);


const std::string DEFAULT_TEXT = "ERROR - NO TEXT";
const int DEFAULT_TEXT_SIZE = 24;
const sf::Color DEFAULT_TEXT_COLOR = sf::Color::White;
const uint32_t DEFAULT_TEXT_STYLE = sf::Text::Bold;

const int TOTAL_BALLS = 50;
const double DELTA_BALLS = 0.35f;   // time between balls
const int INITIAL_CREDITS = 5;      // initial credits

#endif // CONSTANTS_H
