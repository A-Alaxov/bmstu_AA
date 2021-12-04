#ifndef INC_05_TIMER_HPP
#define INC_05_TIMER_HPP

#include "object.hpp"
#include <algorithm>

class Timer {
public:
    void set_size(int n);

    void add_time(bool is_waiting, clock_t time, int task);

    void add_time_from_start(clock_t time, int task);

    void calculate();

    vector<vector<clock_t>> get_waiting_times();

    vector<vector<clock_t>> get_working_times();

    vector<clock_t> get_min_time();

    vector<clock_t> get_max_time();

    vector<double> get_avg_time();

    vector<clock_t> get_proc_time();

    vector<vector<clock_t>> get_time_from_start();

private:
    vector<vector<clock_t>> waiting_times;
    vector<vector<clock_t>> working_times;
    vector<vector<clock_t>> time_from_start;
    vector<clock_t> min_time;
    vector<clock_t> max_time;
    vector<double> avg_time;
    vector<clock_t> proc_time;
};


#endif //INC_05_TIMER_HPP
