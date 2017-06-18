#include "formula.h"

using namespace std;

Formula::Formula() : myVector()
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

int Formula::findAverageWeight()
{
    int clauses = 0;
    int averageWeight = 0;
    for(Clause* c: myVector){
        ++clauses;
        averageWeight += c->getWeight();
    }
    averageWeight /= clauses;
    return averageWeight;
}
// TODO: optimize for 3-SAT
bool Formula::check(const Assignment &assignment) const
{
    for(Clause* c : myVector) {
        if(!c->isSatisfiable(assignment)){
            return false;
        }
    }
    return true;
}

