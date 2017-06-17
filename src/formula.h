#include <vector>
#include <fstream>

#include "clause.h"
#include "assignment.h"

class Formula
{
 private:
  std::vector<Clause *> myVector;
  
 public:
  Formula();
  ~Formula();

  void add(Clause *c);
  
  int size() const;
  Clause* operator[](int index) const;

  bool check(const Assignment &assignment) const;
};
