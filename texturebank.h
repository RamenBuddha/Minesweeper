//
// Created by shaoy on 4/12/2023.
//

#ifndef PROJECT3_TEXTUREBANK_H
#define PROJECT3_TEXTUREBANK_H
#include <map>
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;

class Texturebank {
private:
    map<string,sf::Texture> textureBank;
public:
    Texturebank();
    sf::Texture* getTexture(string name);
};


#endif //PROJECT3_TEXTUREBANK_H
