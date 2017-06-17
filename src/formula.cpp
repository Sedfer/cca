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

// TODO: optimize for 3-SAT
bool Formula::check(const Assignment &assignment) const
{
  for(auto c : myVector) {
    for(int i = 0; i < c->size(); ++i) {
      bool sat = false;
      for(int j = 0; j < assignment.size(); ++j) {
        int var = i;
	if(!assignment[j]) {
	  var *= -1;
	}

	if(c->get(var)) {
	  sat = true;
	  break;
	}
      }

      if(!sat)
	return false;
    }
  }

  return true;
}
