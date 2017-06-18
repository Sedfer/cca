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
    std::set<Variable *> ccdVars;
    std::set<Variable *> sdVars;

    int myVars;
    int myClauses;
    int flips;

    int maxSteps = 200;

    void init();
    void initNeighbours();

    Variable& pickVar();
    void flipVar(Variable& var);
    void updateScores();
    void updateSets();

    void printAssignment() const;

public:
    CcaSolver();

    int vars() const;

    void readFromFile(std::ifstream &file);
    void run();
};
