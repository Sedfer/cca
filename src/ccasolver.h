#pragma once

#include <fstream>

#include "formula.h"
#include "assignment.h"
#include "variable.h"

class CcaSolver
{
private:
    Formula myFormula;

    std::set<Variable *> ccdVars;
    std::set<Variable *> sdVars;

    int myVars;
    int myClauses;

    void init();

    Variable& pickVar();
    void flipVar(Variable& var);
    void updateSets();

    void printAssignment() const;

public:
    CcaSolver();

    int vars() const;

    void readFromFile(std::ifstream &file);
    void run();
};
