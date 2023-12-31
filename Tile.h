//
// Created by shaoy on 4/11/2023.
//

#ifndef PROJECT3_TILE_H
#define PROJECT3_TILE_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "texturebank.h"
using namespace std;

struct Tile {
    bool hasMine = false;
    bool isFlagged = false;
    bool isRevealed = false;
    vector<Tile*> adjacent;
    sf::Sprite visual;
    sf::Sprite flag;
    sf::Sprite mine;
    sf::Sprite number;
};


#endif //PROJECT3_TILE_H
