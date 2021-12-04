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

void create_log(clock_t time1, clock_t time2, int n, Timer timer){
    FILE *f;
    f = fopen("../log.txt", "w");
    timer.calculate();

    fprintf(f,"%7s|", "Конв. №");
    fprintf(f,"%8s|", "Задача №");
    fprintf(f, "%s|", "Постановки в очередь");
    fprintf(f, "%s|", "Ожидания в очереди");
    fprintf(f, "%s|", "Начала обработки");
    fprintf(f, "%s|", "Обработки");
    fprintf(f, "%s|", "Окончания обработки");
    fprintf(f, "%s|", "Мин. ожидания в очереди");
    fprintf(f, "%s|", "Макс. ожидания в очереди");
    fprintf(f, "%s|", "Сред/ ожидания в очереди");
    fprintf(f, "%s|\n", "Выполнения");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            fprintf(f,"%7d|", j + 1);
            fprintf(f,"%8d|", i + 1);
            fprintf(f, "%20lf|", (double) timer.get_time_from_start()[i][j * 2] / CLOCKS_PER_SEC);
            fprintf(f, "%18lf|", (double) timer.get_waiting_times()[i][j] / CLOCKS_PER_SEC);
            fprintf(f, "%16lf|", (double) timer.get_time_from_start()[i][j * 2 + 1] / CLOCKS_PER_SEC);
            fprintf(f, "%9lf|", (double) timer.get_working_times()[i][j] / CLOCKS_PER_SEC);

            fprintf(f, "%19lf|", (double) timer.get_time_from_start()[i][6] / CLOCKS_PER_SEC);
            fprintf(f, "%23lf|", (double) timer.get_min_time()[i] / CLOCKS_PER_SEC);
            fprintf(f, "%24lf|", (double) timer.get_max_time()[i] / CLOCKS_PER_SEC);
            fprintf(f, "%24lf|", timer.get_avg_time()[i]);
            fprintf(f, "%10lf|\n", (double) timer.get_proc_time()[i] / CLOCKS_PER_SEC);
        }
    }

    fprintf(stdout, "Time with conveyor: %lf\n", (double) time1 / CLOCKS_PER_SEC);
    fprintf(stdout, "Time without conveyor: %lf\n", (double) time2 / CLOCKS_PER_SEC);
    fclose(f);
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
        cur_obj.caesar();
        cur_obj.upper_lower();
        cur_obj.reverse();
        res.push_back(cur_obj);
    }

    create_log(time, clock() - start_t, n, conv.get_timer());

    return 0;
}
