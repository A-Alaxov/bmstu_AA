#include <iostream>
#include <string>
#include "time_compare.hpp"
#include "manual_input.hpp"

using namespace std;

int main() {
    size_t rc;
    cout << "Type 1 to manually enter\n"
            "Type 2 to compare time\n"
            "Type anything else to exit\n";
    cin >> rc;
    while (rc == 1 || rc == 2) {
        if (rc == 1) {
            manual_input();
        }
        else {
            time_compare();
        }
        cout << "Type 1 to manually enter\n"
                "Type 2 to compare time\n"
                "Type anything else to exit\n";
        cin >> rc;
    }
    return 0;
}
