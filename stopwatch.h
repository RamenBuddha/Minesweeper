//
// Created by shaoy on 4/16/2023.
//

#ifndef PROJECT3_STOPWATCH_H
#define PROJECT3_STOPWATCH_H
#include <chrono>
using namespace std::chrono;

class Stopwatch {
private:
    time_point<high_resolution_clock> old;
    time_point<high_resolution_clock> now;
    duration<int> dur;
public:
    void start();
    void stop();
    time_point<high_resolution_clock>& getOld();
    time_point<high_resolution_clock>& getNow();
    int getDuration();
    int compensate(time_point<high_resolution_clock>& now, time_point<high_resolution_clock>& old);
};


#endif //PROJECT3_STOPWATCH_H
