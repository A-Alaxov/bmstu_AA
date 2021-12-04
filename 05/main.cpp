#include "conveyor.hpp"
#include <cstdlib>

int get_random_number(int min, int max)
{
    int num = min + rand() % (max - min + 1);
    return num;
}

string generate() {
    string s = "";
    int code = 0;
    int min_low = 48;
    int max_low = 90;
    for (int i = 0; i < 1000000; i++){
        code = get_random_number(min_low, max_low);
        s.push_back(code);
    }
    return s;
}

void create_log(clock_t time1, clock_t time2, int n, Timer timer, vector<Object> res1, vector<Object> res2){
    FILE *f, *fres;
    f = fopen("../log.csv", "w");
    fres = fopen("../res.txt", "w");
    timer.calculate();

    fprintf(f,"%s,", "Conv");
    fprintf(f,"%s,", "Task");
    fprintf(f, "%s,", "QueueEntry");
    fprintf(f, "%s,", "Queue_wait");
    fprintf(f, "%s,", "Processing_start");
    fprintf(f, "%s,", "Processing");
    fprintf(f, "%s,", "ProcessingEnd");
    fprintf(f, "%s,", "Min_queue_wait");
    fprintf(f, "%s,", "Max_queue_wait");
    fprintf(f, "%s,", "Avg_queue_wait");
    fprintf(f, "%s,\n", "     Total");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            fprintf(f,"%4d,", j + 1);
            fprintf(f,"%4d,", i + 1);
            fprintf(f, "%11lf,", (double) timer.get_time_from_start()[i][j * 2] / CLOCKS_PER_SEC);
            fprintf(f, "%10lf,", (double) timer.get_waiting_times()[i][j] / CLOCKS_PER_SEC);
            fprintf(f, "%16lf,", (double) timer.get_time_from_start()[i][j * 2 + 1] / CLOCKS_PER_SEC);
            fprintf(f, "%10lf,", (double) timer.get_working_times()[i][j] / CLOCKS_PER_SEC);

            fprintf(f, "%14lf,", (double) timer.get_time_from_start()[i][6] / CLOCKS_PER_SEC);
            fprintf(f, "%14lf,", (double) timer.get_min_time()[i] / CLOCKS_PER_SEC);
            fprintf(f, "%14lf,", (double) timer.get_max_time()[i] / CLOCKS_PER_SEC);
            fprintf(f, "%14lf,", timer.get_avg_time()[i]);
            fprintf(f, "%10lf,\n", (double) timer.get_proc_time()[i] / CLOCKS_PER_SEC);
        }
    }
    fprintf(stdout, "Time with conveyor: %lf\n", (double) time1 / CLOCKS_PER_SEC);
    fprintf(stdout, "Time without conveyor: %lf\n", (double) time2 / CLOCKS_PER_SEC);
    fclose(f);

    for (int i = 0; i < n; i++) {
        fprintf(fres,"%s,", "Задача №   ");
        fprintf(fres,"%5d,", i + 1);
        fprintf(fres,"%s,", "Результат с конвейером  ");
        fprintf(fres,"%10d,", res1[i].get_max());
        fprintf(fres,"%s,", "Результат без конвейера ");
        fprintf(fres,"%10d,", res2[i].get_max());
        fprintf(fres,"%s:\n", "Строка");
        fprintf(fres,"%s\n-------------------------------------------------------------------------------------\n", res1[i].get_str().c_str());
    }
}

int main(){
    srand(time(nullptr));
    cout << "Enter strings count: ";
    int n;
    cin >> n;
    if (n <= 0){
        cout << "Incorrect";
        return -1;
    }

    vector<Object> res;
    vector<string> objvec;
    objvec.resize(n);

    for (int i = 0; i < n; i++){
        string s = generate();
        objvec[i] = (s);
    }

    conveyor conv(n);

    clock_t start_t = conv.process(objvec);
    clock_t time = clock() - start_t;
    start_t = clock();

    for (int i = 0; i < n; i++) {
        Object cur_obj = Object(objvec[i], i, clock());
        cur_obj.to_words();
        cur_obj.numbers();
        cur_obj.maximum();
        res.push_back(cur_obj);
    }

    create_log(time, clock() - start_t, n, conv.get_timer(), conv.get_res(), res);

    return 0;
}
