#pragma once

#include <vector>
#include <set>

struct Variable
{
    int value;  //variable number: 0,1,2,3,4...

    std::vector<int> clauses;
    int score;
    std::set<Variable *> neighbours;
    bool confChanged;
    bool recorded;
    int age;

    Variable();
    Variable(int _value);
};
