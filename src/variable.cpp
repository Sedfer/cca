#include "variable.h"

Variable::Variable() : Variable(0)
{ }

Variable::Variable(int _value)
    : value(_value), clauses(), score(0), neighbours(),
      confChanged(false), recorded(false), age(0)
{ }
