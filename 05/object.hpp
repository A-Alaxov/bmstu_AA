#ifndef INC_05_OBJECT_HPP
#define INC_05_OBJECT_HPP

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

struct my_facet : std::ctype<char>
{
    using parent_t = std::ctype<char>;
    my_facet(std::size_t refs = 0): parent_t(make_table(), false, refs) {}
    static const mask* make_table()
    {
        static mask char_table[table_size];
        static int fake = (std::copy(classic_table(), classic_table() + table_size, char_table), (void)fake, 0);
        char_table[':'] |= space;
        char_table[';'] |= space;
        char_table['<'] |= space;
        char_table['='] |= space;
        char_table['>'] |= space;
        char_table['?'] |= space;
        char_table['@'] |= space;
        return char_table;
    }
};

class Object {
public:
    Object(string str, int task_num, clock_t time) {
        this->str = str;
        this->task_num = task_num;
        this->time = time;
    }

    void to_words();
    void numbers();
    void maximum();

    string get_str() { return str; };
    int get_max() { return maxim; };

    int task_num;
    clock_t time;

private:
    string str;
    vector<string> words;
    vector<int> numbs;
    int maxim;
};


#endif //INC_05_OBJECT_HPP
