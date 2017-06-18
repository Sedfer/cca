#include "clause.h"

#include <cstdlib>
#include <iostream>
using namespace std;

Clause::Clause() : vars(), myWeight(0), mySat(0)
{ }

int Clause::size() const
{
    return vars.size();
}

void Clause::set(int var, bool pos)
{
    if(pos){
        vars.push_back(var);
    }
    else{
        vars.push_back(-var);
    }
}

void Clause::unset(int var, bool pos)
{
    // TODO: implement
}

bool Clause::get(int var, bool pos) const
{
    ++var;//в Variables индексация с нуля, здесь с 1
    for(auto it = vars.begin(); it != vars.end(); it++)
    {
        if(pos){
            if(*it == var)
                return true;
        }
        else{
            if(*it == -var)
                return true;
        }
    }
    return false;
}

std::vector<int> Clause::getVariables()
{
    std::vector<int> result(size());
    for(int i = 0; i < size(); i++)
    {
        result[i] = abs(vars[i]) - 1;
    }
    return result;
}

void Clause::setWeight(int weight)
{
    myWeight = weight;
}

int Clause::getWeight() const
{
    return myWeight;
}

bool Clause::updateSat(const Assignment &assignment)
{
    for(int var : vars) {
        if((var > 0 && assignment[var - 1]) ||
           (var < 0 && !assignment[-var - 1])) {
            mySat = true;
            return mySat;
        }
    }

    mySat = false;
    return mySat;
}

bool Clause::isSatisfiable() const
{
    return mySat;
}

int Clause::getScore(int flipedVar, const Assignment &assignment)
{
    bool newSat = false;
    for(int var : vars) {
        if(var - 1 == flipedVar) {
            if(!assignment[flipedVar]) {
                newSat = true;
                break;
            }

            continue;
        }

        if(-var - 1 == flipedVar) {
            if(assignment[flipedVar]) {
                newSat = true;
                break;
            }

            continue;
        }

        if((var > 0 && assignment[var - 1]) ||
           (var < 0 && !assignment[-var - 1])) {
            newSat = true;
            break;
        }
    }

    int score = 0;
    if(!isSatisfiable())
        score = getWeight();

    if(!newSat) {
        score -= getWeight();
    }

    return score;
}
