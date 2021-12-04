#ifndef INC_05_CONVEYOR_HPP
#define INC_05_CONVEYOR_HPP

#include "timer.hpp"
#include <queue>
#include <mutex>
#include <thread>

class conveyor {
public:
    conveyor(int n) : n(n) {};

    clock_t process(vector<string> objvec);

    Timer get_timer();

private:
    void first_conv();
    void second_conv();
    void third_conv();

    clock_t start_t;

    queue<Object> queue1;
    queue<Object> queue2;
    queue<Object> queue3;

    vector<Object> res;

    mutex m1, m2, m3, resm;

    int n;

    Timer timer;
};


#endif //INC_05_CONVEYOR_HPP
