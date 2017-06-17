#pragma once

#include <vector>

struct Variable
{
  int value;

  bool assigned;
  int score;
  std::vector<Variable *> neighbours;
  bool confChanged;
  bool recorded;

  Variable();
  Variable(int _value);
};
