#include "formula.h"

using namespace std;

Formula::Formula() : myVector(), myAssignment()
{ }

Formula::~Formula()
{
    for(Clause *c : myVector){
        delete c;
    }
}

int Formula::size() const
{
    return myVector.size();
}

void Formula::add(Clause *c)
{
    myVector.push_back(c);
}

void Formula::init(int vars)
{
    myAssignment.resize(vars);
    myVariables.resize(vars);
    for(int i = 0; i < vars; ++i) {
        myVariables[i] = new Variable();
        myVariables[i]->value = i;
        myVariables[i]->score = 0;
        myVariables[i]->confChanged = true;
        myVariables[i]->recorded = false;

        myAssignment[i] = bool(rand() % 2);
    }

    for(Clause* c: myVector)
    {
        c->setWeight(1);
    }

    initNeighboursAndClauses();

    for(auto c : myVector) {
        c->updateSat(myAssignment);
    }
}

void Formula::initNeighboursAndClauses()
{
    for(int i = 0; i < size(); ++i){
        auto vars = myVector[i]->getVariables();
        for(int j = 0; j < vars.size(); j++){
            for(int k = 0; k < vars.size(); k++){
                if(j != k)
                    myVariables[vars[j]]->neighbours.insert(myVariables[vars[k]]);
            }

            myVariables[vars[j]]->clauses.push_back(i);
        }
    }
}

Clause* Formula::operator[](int index) const
{
    return myVector[index];
}

vector<Clause *>::const_iterator Formula::begin() const
{
    return myVector.cbegin();
}

vector<Clause *>::const_iterator Formula::end() const
{
    return myVector.cend();
}

Assignment &Formula::getAssignment()
{
    return myAssignment;
}

const Assignment &Formula::getAssignment() const
{
    return myAssignment;
}

std::vector<Variable *> &Formula::getVariables()
{
    return myVariables;
}

const std::vector<Variable *> &Formula::getVariables() const
{
    return myVariables;
}

int Formula::findAverageWeight()
{
    int averageWeight = 0;
    for(Clause* c: myVector){
        averageWeight += c->getWeight();
    }
    averageWeight /= size();

    return averageWeight;
}

bool Formula::check() const
{
    for(Clause* c : myVector) {
        if(!c->isSatisfiable()){
            return false;
        }
    }

    return true;
}

void Formula::flipVar(int varIndex)
{
    Variable &var = *(myVariables[varIndex]);

    var.confChanged = false;
    for(Variable* v : var.neighbours) {
        v->confChanged = true;
    }

    var.age = 0;

    myAssignment[varIndex].flip();

    // update changed clauses
    for(int c : var.clauses) {
        myVector[c]->updateSat(myAssignment);
    }

    // update changed scores
    updateScore(var);
    for(auto neighbour : var.neighbours) {
        updateScore(*neighbour);
    }
}

void Formula::updateWeights()
{
    for(auto c : myVector){
        if(!c->isSatisfiable()) {
            c->setWeight(c->getWeight() + 1);
        }
    }

    int averageWeight = findAverageWeight();
    if(averageWeight > 300) {
        for(auto c : myVector){
            c->setWeight(c->getWeight() * 0.3 + (1 - 0.3) * averageWeight);
        }
    }

    updateScores();
}

void Formula::updateScores()
{
    for(auto var : myVariables) {
        updateScore(*var);
    }
}

void Formula::updateScore(Variable &var)
{
    var.score = 0;
    for(int c : var.clauses) {
        var.score += myVector[c]->getScore(var.value, myAssignment);
    }
}
