//
// Created by shaoy on 4/11/2023.
//

#ifndef PROJECT3_BOARD_H
#define PROJECT3_BOARD_H
#include <vector>
#include "Tile.h"
#include "texturebank.h"
#include <random>
#include <windows.h>
using namespace std;


class Board {
private:
    std::mt19937 random_mt;
    int rows;
    int cols;
    int mineCount;
    int size;
    vector<vector<Tile>> board;
    /* implement rng system for random mines */

public:
    Board(int rows, int cols, int mineCount);
    int Random(int minX, int maxX, int minY, int maxY);
    void setadj();
    vector<vector<Tile>>& getBoard();
    void revealNeighbor(Tile* tile);
    bool checkWin();
    int countMines(Tile& tile);
    void reset();
    int getSize();
    int getRow();
    int getCols();
};


#endif //PROJECT3_BOARD_H
