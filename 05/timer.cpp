#include "timer.hpp"

void Timer::set_size(int n) {
    waiting_times.resize(n);
    working_times.resize(n);
    time_from_start.resize(n);

    for (int i = 0; i < n; i++) {
        waiting_times[i].resize(0);
        working_times[i].resize(0);
        time_from_start[i].resize(0);
    }
    min_time.resize(0);
    max_time.resize(0);
    avg_time.resize(0);
    proc_time.resize(0);
}

void Timer::add_time(bool is_waiting, clock_t time, int task) {
    if (is_waiting)
        waiting_times[task].push_back(time);
    else
        working_times[task].push_back(time);
}

void Timer::add_time_from_start(clock_t time, int task) {
    time_from_start[task].push_back(time);
}

void Timer::calculate() {
    for (int i = 0; i < waiting_times.size(); i++){
        auto minmax = std::minmax_element(waiting_times[i].begin(), waiting_times[i].end());
        min_time.push_back(*minmax.first);
        max_time.push_back(*minmax.second);

        double sum_of_el = 0;
        for (auto& c : waiting_times[i])
            sum_of_el += (double) c / CLOCKS_PER_SEC;

        avg_time.push_back(sum_of_el / waiting_times[i].size());
    }

    for (int i = 0; i < working_times.size(); i++) {
        auto sum_of_el = 0;
        for (auto& c : working_times[i])
            sum_of_el += c;
        proc_time.push_back(sum_of_el);
    }
}

vector<vector<clock_t>> Timer::get_waiting_times() {
    return waiting_times;
}

vector<vector<clock_t>> Timer::get_working_times() {
    return working_times;
}

vector<clock_t> Timer::get_min_time() {
    return min_time;
}

vector<clock_t> Timer::get_max_time() {
    return max_time;
}

vector<double> Timer::get_avg_time() {
    return avg_time;
}

vector<clock_t> Timer::get_proc_time() {
    return proc_time;
}

vector<vector<clock_t>> Timer::get_time_from_start() {
    return time_from_start;
}
