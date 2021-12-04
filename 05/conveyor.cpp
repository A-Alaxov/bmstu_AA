#include "conveyor.hpp"

void conveyor::first_conv() {
    int num = 0;
    while (true) {
        if (num == n)
            break;
        m1.lock();
        if (queue1.empty()) {
            m1.unlock();
            continue;
        }
        Object cur_obj = queue1.front();
        timer.add_time_from_start(queue1.front().time, cur_obj.task_num);
        timer.add_time_from_start(clock() - start_t, cur_obj.task_num);
        timer.add_time(1, clock() - queue1.front().time, queue1.front().task_num);
        queue1.pop();

        clock_t cur_time = clock();
        m1.unlock();
        cur_obj.caesar();
        m2.lock();
        timer.add_time_from_start(clock() - start_t, cur_obj.task_num);
        timer.add_time(0, clock() - cur_time, cur_obj.task_num);

        queue2.push(cur_obj);
        m2.unlock();
        num++;
    }
}

void conveyor::second_conv() {
    int num = 0;
    while (true) {
        if (num == n)
            break;
        m2.lock(); // wait in queue
        if (queue2.empty()) {
            m2.unlock();
            continue;
        }
        Object cur_obj = queue2.front();
        timer.add_time_from_start(clock() - start_t, cur_obj.task_num);
        timer.add_time(1, clock() - queue2.front().time, queue2.front().task_num);
        queue2.pop();

        clock_t cur_time = clock();
        m2.unlock();
        cur_obj.upper_lower();
        m3.lock();
        timer.add_time_from_start(clock() - start_t, cur_obj.task_num);
        timer.add_time(0, clock() - cur_time, cur_obj.task_num);

        queue3.push(cur_obj);
        m3.unlock();
        num++;
    }
}

void conveyor::third_conv() {
    int num = 0;
    while (true) {
        if (num == n)
            break;
        m3.lock(); // wait in queue
        if (queue3.empty()) {
            m3.unlock();
            continue;
        }
        Object cur_obj = queue3.front();
        timer.add_time_from_start(clock() - start_t, cur_obj.task_num);
        timer.add_time(1, clock() - queue3.front().time, queue3.front().task_num);
        queue3.pop();

        clock_t cur_time = clock();
        m3.unlock();
        cur_obj.reverse();
        resm.lock();
        timer.add_time_from_start(clock() - start_t, cur_obj.task_num);
        timer.add_time(0, clock() - cur_time, cur_obj.task_num);

        res.push_back(cur_obj);
        resm.unlock();
        num++;
    }
}

clock_t conveyor::process(vector<string> objvec) {
    timer.set_size(n);

    start_t = clock();

    thread t1(&conveyor::first_conv, this);
    thread t2(&conveyor::second_conv, this);
    thread t3(&conveyor::third_conv, this);

    for (int i = 0; i < n; i++) {
        m1.lock();
        queue1.push(Object(objvec[i], i, clock()));
        m1.unlock();
    }

    t1.join();
    t2.join();
    t3.join();

    return start_t;
}

Timer conveyor::get_timer() {
    return timer;
}
