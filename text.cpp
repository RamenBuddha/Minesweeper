//
// Created by shaoy on 4/10/2023.
//
#include "text.h"

void setEverything(sf::Text& conductor, const sf::Font& font, string style, string color, int size) {
    conductor.setFont(font);
    conductor.setCharacterSize(size);
    if (color == "yellow" or color == "Yellow"){
        conductor.setFillColor(sf::Color::Yellow);
    } else {
        conductor.setFillColor(sf::Color::White);
    }
    if (style == "B") {
        conductor.setStyle(sf::Text::Bold);
    } else if (style == "U") {
        conductor.setStyle(sf::Text::Underlined);
    } else if (style == "BU" or style == "UB") {
        conductor.setStyle(sf::Text::Bold | sf::Text::Underlined);
    }
}


void setText(sf::Text &text, float x, float y){
     sf::FloatRect textRect = text.getLocalBounds();
     text.setOrigin(textRect.left + textRect.width/2.0f,
                     textRect.top + textRect.height/2.0f);
     text.setPosition(sf::Vector2f(x, y));
     }

