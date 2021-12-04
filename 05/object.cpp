#include "object.hpp"

void Object::caesar() {
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

void Object::upper_lower() {
    int found;
    for (auto word : words) {
        if (stringstream(word) >> found)
            numbs.push_back(found);
    }
}

void Object::reverse() {
    maxim = numbs[0];
    for (auto numb : numbs) {
        maxim = max(maxim, numb);
    }
}