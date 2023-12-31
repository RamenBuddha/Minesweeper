//
// Created by shaoy on 4/12/2023.
//

#include "texturebank.h"

Texturebank::Texturebank() {
    sf::Texture lol;
    lol.loadFromFile("files/images/debug.png");
    textureBank["debug"] = lol;
    sf::Texture lol1;
    lol1.loadFromFile("files/images/digits.png");
    textureBank["digits"] = lol1;
    sf::Texture lol2;
    lol2.loadFromFile("files/images/face_happy.png");
    textureBank["face_happy"] = lol2;
    sf::Texture lol3;
    lol3.loadFromFile("files/images/face_lose.png");
    textureBank["face_lose"] = lol3;
    sf::Texture lol4;
    lol4.loadFromFile("files/images/face_win.png");
    textureBank["face_win"] = lol4;
    sf::Texture lol5;
    lol5.loadFromFile("files/images/flag.png");
    textureBank["flag"] = lol5;
    sf::Texture lol6;
    lol6.loadFromFile("files/images/leaderboard.png");
    textureBank["leaderboard"] = lol6;
    sf::Texture lol7;
    lol7.loadFromFile("files/images/mine.png");
    textureBank["mine"] = lol7;
    sf::Texture lol8;
    lol8.loadFromFile("files/images/number_1.png");
    textureBank["1"] = lol8;
    sf::Texture lol9;
    lol9.loadFromFile("files/images/number_2.png");
    textureBank["2"] = lol9;
    sf::Texture lol10;
    lol10.loadFromFile("files/images/number_3.png");
    textureBank["3"] = lol10;
    sf::Texture lol11;
    lol11.loadFromFile("files/images/number_4.png");
    textureBank["4"] = lol11;
    sf::Texture lol12;
    lol12.loadFromFile("files/images/number_5.png");
    textureBank["5"] = lol12;
    sf::Texture lol13;
    lol13.loadFromFile("files/images/number_6.png");
    textureBank["6"] = lol13;
    sf::Texture lol14;
    lol14.loadFromFile("files/images/number_7.png");
    textureBank["7"] = lol14;
    sf::Texture lol15;
    lol15.loadFromFile("files/images/number_8.png");
    textureBank["8"] = lol15;
    sf::Texture lol16;
    lol16.loadFromFile("files/images/pause.png");
    textureBank["pause"] = lol16;
    sf::Texture lol17;
    lol17.loadFromFile("files/images/play.png");
    textureBank["play"] = lol17;
    sf::Texture lol18;
    lol18.loadFromFile("files/images/tile_hidden.png");
    textureBank["tile_hidden"] = lol18;
    sf::Texture lol19;
    lol19.loadFromFile("files/images/tile_revealed.png");
    textureBank["tile_revealed"] = lol19;
}

sf::Texture* Texturebank::getTexture(string name) {
    return &textureBank[name];
}