#include "assignment.h"

Assignment::Assignment() : Assignment(0)
{ }

Assignment::Assignment(int size) : myVector(size)
{ }

void Assignment::resize(int newSize)
{
    myVector.resize(newSize);
}

int Assignment::size() const
{
    return myVector.size();
}

std::vector<bool>::reference Assignment::operator[](int index)
{
    return myVector[index];
}

std::vector<bool>::const_reference Assignment::operator[](int index) const
{
    return myVector[index];
}
