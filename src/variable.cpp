#include "variable.h"

Variable::Variable() : Variable(0)
{ }

Variable::Variable(int _value)
    : value(_value), assigned(false), score(0), neighbours(),
      confChanged(false), recorded(false), flip(0)
{ }
