#include "clause.h"

#include <cstdlib>
using namespace std;

Clause::Clause(int size) : myWeight(0)
{
  p = vector<bool>(size, false);
  n = vector<bool>(size, false);
}

int Clause::size() const
{
  return p.size();
}

void Clause::set(int var, bool value)
{
  bool pos = var > 0;
  var = abs(var);
  
  if(var > p.size() || var == 0){
    throw nullptr;
  }

  if(pos){
    p[var-1] = value;
  }
  else{
    n[var-1] = value;
  }
}

bool Clause::get(int var) const
{
  bool pos = var > 0;
  var = abs(var);

  if(var > p.size() || var == 0){
    throw nullptr;
  }

  if(pos){
    return p[var-1];
  }
  else{
    return n[var-1];
  }
}

void Clause::setWeight(int weight)
{
  myWeight = weight;
}

int Clause::getWeight() const
{
  return myWeight;
}
