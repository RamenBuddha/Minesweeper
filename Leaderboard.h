//
// Created by shaoy on 4/17/2023.
//

#ifndef PROJECT3_LEADERBOARD_H
#define PROJECT3_LEADERBOARD_H
#include <string>
#include <map>
#include <utility>
#include <fstream>
using namespace std;

struct Leaderboard {
    map<string,pair<int, string>> leaderboard;
    void readFromFile(string name);
    const void readFromFile();
    void sort();
    static void writeToFile(string time, string name);
};


#endif //PROJECT3_LEADERBOARD_H
