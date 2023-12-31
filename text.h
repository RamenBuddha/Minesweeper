//
// Created by shaoy on 4/10/2023.
//

#ifndef PROJECT3_TEXT_H
#define PROJECT3_TEXT_H
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

void setEverything(sf::Text&, const sf::Font& font, string style, string color, int size);
void setText(sf::Text &text, float x, float y);

#endif //PROJECT3_TEXT_H
