#include "object.hpp"

void Object::to_words() {
    stringstream ss;
    ss << str;

    ss.imbue(std::locale(ss.getloc(), new my_facet()));

    string temp;
    while (!ss.eof()) {
        ss >> temp;
        words.push_back(temp);
        temp = "";
    }
}

void Object::numbers() {
    int found;
    for (auto word : words) {
        if (stringstream(word) >> found)
            numbs.push_back(found);
    }
}

void Object::maximum() {
    if (numbs.empty()) {
        maxim = 0;
        return;
    }
    maxim = numbs[0];
    for (auto numb : numbs) {
        maxim = max(maxim, numb);
    }
}