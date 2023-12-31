//
// Created by shaoy on 4/17/2023.
//

#include "Leaderboard.h"
using namespace std;

void Leaderboard::readFromFile(string name) {
    ifstream stream("files/leaderboard.txt");
    string temp;
    string temp2;
    int i = 1;
    while (!stream.eof()) {
        getline(stream, temp, ',');
        getline(stream, temp2);
        if (temp2 == name) {
            leaderboard[temp] = pair<int, string>(i, temp2 + '*');
        } else {
            leaderboard[temp] = pair<int, string>(i, temp2);
        }
        i++;
    }
    this->sort();
}
const void Leaderboard::readFromFile() {
    ifstream stream("files/leaderboard.txt");
    string temp;
    string temp2;
    int i = 1;
    while (!stream.eof()) {
        getline(stream, temp, ',');
        getline(stream, temp2);
        leaderboard[temp] = pair<int, string>(i, temp2);
        i++;
    }
    this->sort();
}

void Leaderboard::sort() {
    int j = 1;
    for (auto i = leaderboard.begin(); i != leaderboard.end(); i++) {
        leaderboard[i->first].first = j;
        j++;
    }
}

void Leaderboard::writeToFile(string time, string name) {
    ofstream stream("files/leaderboard.txt", ios_base::app);
        stream << "\n" + time + "," + name;
    }
