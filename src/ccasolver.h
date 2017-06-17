#pragma once

#include <fstream>

#include "formula.h"
#include "assignment.h"
#include "variable.h"

class CcaSolver
{
 private:
  Formula myFormula;
  Assignment myAssignment;
  std::vector<Variable *> myVariables;
  std::vector<Variable *> ccdVars;

  int myVars;
  
  void init();
  void initNeighbours();

  int pickVar();
  void flipVar(int var);
  
  void printAssignment() const;
  
 public:
  CcaSolver();

  int vars() const;

  void readFromFile(std::ifstream &file);
  void run();
};
