#pragma once

#include <vector>
#include <set>

struct Variable
{
  int value;//variable number: 0,1,2,3,4...

  bool assigned;//variable value: 1/0
  int score;
  std::set<Variable *> neighbours;
  bool confChanged;
  bool recorded;
  int flip;

  Variable();
  Variable(int _value);
};
