#include <cstdlib>
#include <iostream>

#include "ccasolver.h"

using namespace std;

CcaSolver::CcaSolver()
  : myFormula(), myAssignment(), myVariables(), ccdVars(), sdVars(), myVars(0), myClauses(0), flips(0)
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
  myVariables.resize(vars());
  for(int i = 0; i < vars(); ++i) {
    myVariables[i]->value = i;
    myVariables[i]->assigned = bool(rand() % 2);
    myAssignment[i] = myVariables[i]->assigned;
    myVariables[i]->score = 0;
    myVariables[i]->confChanged = true;
    myVariables[i]->recorded = false;
  }
  for(Clause* c: myFormula)
  {
	  c->setWeight(1);
  }
  updateScores();
  updateSets();
  initNeighbours();
}

void CcaSolver::initNeighbours()
{
	for(Clause* c : myFormula){
		auto v = c->getVariables();
		for(int i = 0; i < v.size(); i++){
			for(int j = 0; j < v.size(); j++){
				if(i != j)
					myVariables[v[i]]->neighbours.insert(myVariables[v[j]]);
			}
		}
	}
}

void CcaSolver::run()
{
  while(true) {
    if(myFormula.check(myAssignment)) {
      printAssignment();
      return;
    }

    Variable& var = pickVar();
    flipVar(var);
  }
}
//TODO: resolve ties to older variable
//parametric functions??
Variable& CcaSolver::pickVar()
{
	Variable* result;
	
	//greedy
	if(!ccdVars.empty()){
		result = *(ccdVars.begin());
		for(Variable* v: ccdVars){
			if(v->score > result->score)
				result = v;
		}
		
	}
	else if(!sdVars.empty()){
		result = *(sdVars.begin());
		for(Variable* v: sdVars){
			if(v->score > result->score)
				result = v;
		}
		
	}
	//diversification
	else{
		for(Clause* c:myFormula){
			if(!c->isSatisfiable(myAssignment))
				c->setWeight(c->getWeight() + 1);
		}
		int averageWeight = myFormula.findAverageWeight();
		if(averageWeight > 300){
			for(Clause* c:myFormula){
				c->setWeight(c->getWeight() * 0.3 + (1 - 0.3) * averageWeight);
			}
		}
		int amount = 0;
		for(Clause* c:myFormula){
			if (!c->isSatisfiable(myAssignment))
				amount++;
		}
		amount = random() % amount;
		Clause* myClause;
		for(Clause* c:myFormula){
			if (!c->isSatisfiable(myAssignment)){
				if(amount == 0){
					myClause = c;
					break;
				}
				amount--;
			}
		}
		auto v = myClause->getVariables();
		int min = flips;
		for(int i = 0; i < v.size(); i++)
		{
			if(myVariables[i]->flip < min){
				min = myVariables[i]->flip;
				result = myVariables[i];
			}
		}
		updateScores();
		updateSets();
	}
	return *result;
}

void CcaSolver::flipVar(Variable& var)
{
  var.confChanged = false;
  for(Variable* v : var.neighbours)
  {
	  v->confChanged = true;
  }
	  
  var.assigned = !var.assigned;
  myAssignment[abs(var.value)].flip();
  flips++;
  var.flip = flips;
		
  updateScores();
  updateSets();
}

void CcaSolver::updateScores()
{
	for(Variable* v: myVariables){
	  int cost = 0;
	  int reverseCost = 0;
	  for(Clause* c : myFormula){
		  if(!c->isSatisfiable(myAssignment))
			cost += c->getWeight();
	  }
	  myAssignment[v->value].flip();
	  for(Clause* c : myFormula){
		  if(!c->isSatisfiable(myAssignment))
			reverseCost += c->getWeight();
	  }
	  myAssignment[v->value].flip();
	  v->score = cost - reverseCost;
	}
}

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
	
	for(Variable* v: myVariables){
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
  for(int i = 0; i < myAssignment.size(); ++i) {
    if(myAssignment[i]) {
      cout << i << " ";
    } else {
      cout << -i << " ";
    }
  }
  
  cout << endl;
}
