//
// Created by shaoy on 4/12/2023.
//

#ifndef PROJECT3_WINDOWS_H
#define PROJECT3_WINDOWS_H
#include <SFML/Graphics.hpp>
#include "text.h"
#include "board.h"
#include "texturebank.h"
#include "stopwatch.h"
#include "Leaderboard.h"
#include <fstream>
pair<bool,string> welcomeWindow();
void gameWindow(string name);
void leaderWindow(int icol, int irow, bool& leader, bool& gamewin, Stopwatch& watch, Leaderboard& saekki, string name);

#endif //PROJECT3_WINDOWS_H
