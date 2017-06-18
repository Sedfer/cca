#include "clause.h"

#include <cstdlib>
using namespace std;

Clause::Clause() : vars(), myWeight(0)
{
 
}

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

bool Clause::isSatisfiable(const Assignment &assignment) const
{
	 for(int i = 0; i < size(); i++)
	 {
		 if((assignment[abs(vars[i]) - 1] && (vars[i] > 0)) ||
		    (!assignment[abs(vars[i]) - 1] && (vars[i] < 0)))
				return true;
	 }
	 return false;
}
