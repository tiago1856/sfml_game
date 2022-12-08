#include "TextEntity.h"
#include "constants.h"

#include <iostream>

TextEntity::TextEntity(const sf::Font& font, const sf::Vector2f& position)
{
    text.setFont(font);
    text.setString(DEFAULT_TEXT);
    text.setCharacterSize(DEFAULT_TEXT_SIZE);
    text.setFillColor(DEFAULT_TEXT_COLOR);
    text.setStyle(DEFAULT_TEXT_STYLE);
    text.setPosition(position);
};

TextEntity::~TextEntity()
{
};

void TextEntity::setText(const std::string& msg)
{
    text.setString(msg);
}

sf::Text& TextEntity::getText()
{
    return text;
}

void TextEntity::draw(sf::RenderWindow* window)
{
    if (!bVisible) return;
    window->draw(text);
}

void TextEntity::update(double dt)
{
    if (!bActive) return;
}
