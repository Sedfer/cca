#include <cstdlib>
#include <iostream>

#include "ccasolver.h"

using namespace std;

CcaSolver::CcaSolver()
  : myFormula(), myAssignment(), myVariables(), ccdVars(), myVars(0)
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

  int clauses = 0;
  file >> myVars >> clauses;

  for(int i = 0; i < clauses; ++i){
    Clause *c = new Clause(vars());
    int num;
    while(true){
      file >> num;
      if(num == 0)
	break;

      c->set(num);
    }

    myFormula.add(c);
  }

  init();
}

void CcaSolver::init()
{
  myVariables.resize(vars());
  for(int i = 0; i < vars(); ++i) {
    myVariables[i]->value = i;
    myVariables[i]->assigned = bool(rand() % 2);
    myAssignment[i] = myVariables[i]->assigned;
    myVariables[i]->score = 0;
    myVariables[i]->confChanged = true;
    myVariables[i]->recorded = false;
  }

  initNeighbours();
}

void CcaSolver::initNeighbours()
{
  
}

void CcaSolver::run()
{
  while(true) {
    if(myFormula.check(myAssignment)) {
      printAssignment();
      return;
    }

    int var = pickVar();
    flipVar(var);
  }
}

int CcaSolver::pickVar()
{
  return 0;
}

void CcaSolver::flipVar(int var)
{
  myVariables[var]->assigned = !myVariables[var]->assigned;
  myAssignment[var].flip();
}

void CcaSolver::printAssignment() const
{
  for(int i = 0; i < myAssignment.size(); ++i) {
    if(myAssignment[i]) {
      cout << i << " ";
    } else {
      cout << -i << " ";
    }
  }
  
  cout << endl;
}
