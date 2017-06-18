#include <cstdlib>
#include <iostream>

#include "ccasolver.h"

using namespace std;

CcaSolver::CcaSolver()
    : myFormula(), ccdVars(), sdVars(), myVars(0), myClauses(0)
{ }

int CcaSolver::vars() const
{
    return myVars;
}

void CcaSolver::readFromFile(ifstream &file)
{
    string str;

    while(true){
        file >> str;
        if(str == "c"){
            getline(file, str);
            continue;
        }

        if(str == "p"){
            break;
        }

        throw nullptr;
    }

    file >> str;
    if(str != "cnf")
        throw nullptr;

    file >> myVars >> myClauses;

    for(int i = 0; i < myClauses; ++i){
        Clause *c = new Clause();
        int num;
        while(true){
            file >> num;
            if(num == 0)
                break;
            if(num > 0)
                c->set(num , true);
            else
                c->set(-num, false);
        }

        myFormula.add(c);
    }

    init();
}

void CcaSolver::init()
{
    srand(time(0));

    myFormula.init(vars());

    updateSets();
}

void CcaSolver::run()
{
    while(true) {
        if(myFormula.check()) {
            printAssignment();
            return;
        }

        Variable& var = pickVar();
        flipVar(var);

        // TODO: replace with lastFlip
        for(auto var : myFormula.getVariables()) {
            ++var->age;
        }
    }
}

//parametric functions??
Variable& CcaSolver::pickVar()
{
    Variable* result;

    //greedy
    if(!ccdVars.empty()){
        result = *(ccdVars.begin());
        for(Variable* v: ccdVars){
            if(v->score > result->score) {
                result = v;
            }
            if(v->score == result->score && v->age > result->age) {
                result = v;
            }
        }

    }
    else if(!sdVars.empty()){
        result = *(sdVars.begin());
        for(Variable* v: sdVars){
            if(v->score > result->score) {
                result = v;
            }
            if(v->score == result->score && v->age > result->age) {
                result = v;
            }
        }

    }
    //diversification
    else{
        myFormula.updateWeights();

        // get random unsat clause
        int amount = 0;
        for(Clause* c:myFormula){
            if (!c->isSatisfiable())
                amount++;
        }
        amount = random() % amount;
        Clause* myClause;
        for(Clause* c:myFormula){
            if (!c->isSatisfiable()){
                if(amount == 0){
                    myClause = c;
                    break;
                }
                amount--;
            }
        }

        auto v = myClause->getVariables();
        int maxAge = -1;
        for(int i = 0; i < v.size(); i++)
        {
            if(myFormula.getVariables()[i]->age > maxAge){
                maxAge = myFormula.getVariables()[i]->age;
                result = myFormula.getVariables()[i];
            }
        }

        updateSets();
    }

    return *result;
}

void CcaSolver::flipVar(Variable& var)
{
    myFormula.flipVar(var.value);

    updateSets();
}

// TODO: check if creating sdVars makes any difference
void CcaSolver::updateSets()
{
    int averageWeight = myFormula.findAverageWeight();
    for(Variable* v: ccdVars){
        if(v->score <= 0){
            ccdVars.erase(v);
            v->recorded = false;
        }
    }
    for(Variable* v: sdVars){
        if(v->score <= averageWeight)
            sdVars.erase(v);
    }

    for(Variable* v: myFormula.getVariables()){
        if ((v->score > 0) && (v->confChanged)){
            if(!v->recorded){
                ccdVars.insert(v);
                v->recorded = true;
            }
        }

        if(v->score > averageWeight){
            sdVars.insert(v);
        }
    }
}

void CcaSolver::printAssignment() const
{
    for(int i = 0; i < myFormula.getAssignment().size(); ++i) {
        if(myFormula.getAssignment()[i]) {
            cout << i + 1 << " ";
        } else {
            cout << -(i + 1) << " ";
        }
    }

    cout << endl << "SATISFIABLE" << endl;
}
