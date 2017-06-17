#pragma once

#include <fstream>

#include "formula.h"
#include "assignment.h"

class CcaSolver
{
 private:
  Formula myFormula;
  Assignment myAssignment;
  std::vector<bool> confChanged;

  int myVars;
  
  void init();

  int pickVar();
  void flipVar(int var);
  void printAssignment() const;
 public:
  CcaSolver();

  int vars() const;

  void readFromFile(std::ifstream &file);
  void run();
};
