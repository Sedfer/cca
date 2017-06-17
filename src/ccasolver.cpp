#include <cstdlib>
#include <iostream>

#include "ccasolver.h"

using namespace std;

CcaSolver::CcaSolver()
  : myFormula(), myAssignment(), confChanged(), myVars(0)
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
  myAssignment.resize(vars());
  for(int i = 0; i < vars(); ++i) {
    myAssignment[i] = bool(rand() % 2);
  }

  confChanged.resize(vars());
  for(int i = 0; i < vars(); ++i) {
    confChanged[i] = true;
  }
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
  myAssignment[var] = !myAssignment[var];
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
