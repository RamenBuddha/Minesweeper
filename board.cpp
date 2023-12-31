//
// Created by shaoy on 4/11/2023.
//

#include <stdexcept>
#include <unistd.h>
#include "board.h"
using namespace std;

Board::Board(int rows, int cols, int mineCount) {
    this->rows = rows;
    this->cols = cols;
    this->mineCount = mineCount;
    this->size = rows * cols;
    for (int i = 0; i < rows; i++) {
        vector<Tile> row;
        for (int j = 0; j < cols; j++) {
            Tile temp;
            row.push_back(temp);
        }
        this->board.push_back(row);
    }
    Random(0, this->cols, 0, this->rows);
    setadj();
}

int Board::Random(int minX, int maxX, int minY, int maxY)
{
    random_mt.seed(rand());
    uniform_int_distribution<int> dist(minX, maxX - 1);
    uniform_int_distribution<int> dist2(minY, maxY - 1);
    for (int i = 0; i < this->mineCount;) {
        int randx = dist(random_mt);
        int randy = dist2(random_mt);
        if (this->board[randy][randx].hasMine == false) {
            this->board[randy][randx].hasMine = true;
            i++;
        }
    }

}

void Board::setadj() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    try {
                        this->board.at(i).at(j).adjacent.push_back((&this->board.at(i + k).at(j + l)));
                    } catch (out_of_range& ex) {
                        /* do nothing */
                    }
                }
            }
        }
    }
}

void Board::revealNeighbor(Tile* tile) {
    int count = 0;
    for (int i = 0; i < tile->adjacent.size(); i++) {
        if (tile->adjacent.at(i)->hasMine) {
            count += 1;
        }
    }
    if (count == 0) {
        for (int i = 0; i < tile->adjacent.size(); i++) {
            if (!tile->adjacent.at(i)->isFlagged and !tile->adjacent.at(i)->isRevealed) {
                tile->adjacent.at(i)->isRevealed = true;
                this->revealNeighbor(tile->adjacent.at(i));
            }
        }
    } else {
        return;
    }
}

int Board::countMines(Tile& tile) {
    int count = 0;
    for (int i = 0; i < tile.adjacent.size(); i++) {
        if (tile.adjacent.at(i)->hasMine) {
            count += 1;
        }
    }
    return count;
}

vector<vector<Tile>>& Board::getBoard() {
    return this->board;
}

bool Board::checkWin() {
    int Rcount;
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            if (this->board.at(i).at(j).isRevealed) {
                Rcount += 1;
            }
        }
    }
    if (Rcount == this->size - this->mineCount) {
        return true;
    } else {
        return false;
    }
}

void Board::reset() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->cols; j++) {
            board.at(i).at(j).hasMine = false;
            board.at(i).at(j).isRevealed = false;
            board.at(i).at(j).isFlagged = false;
        }
    }
    Random(0, this->cols, 0, this->rows);
}

int Board::getSize() {
    return this->size;
}

int Board::getRow() {
    return this->rows;
}

int Board::getCols() {
    return this->cols;
}