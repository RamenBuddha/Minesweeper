//
// Created by shaoy on 4/16/2023.
//

#include "stopwatch.h"

void Stopwatch::start() {
    this->old = high_resolution_clock::now();
}

void Stopwatch::stop() {
    this->now = high_resolution_clock::now();
    this->dur = duration_cast<seconds>(now - old);
}

time_point<high_resolution_clock>& Stopwatch::getOld() {
    return this->old;
}

time_point<high_resolution_clock>& Stopwatch::getNow() {
    return this->now;
}

int Stopwatch::getDuration() {
    this->dur = duration_cast<seconds>(now - old);
    return dur.count();
}

int Stopwatch::compensate(time_point<high_resolution_clock>& now, time_point<high_resolution_clock>& old) {
    return duration_cast<seconds>(this->dur - (now - old)).count();
}
