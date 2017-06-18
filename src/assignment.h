#pragma once

#include <vector>

class Assignment
{
private:
    std::vector<bool> myVector;

public:
    Assignment();
    Assignment(const Assignment& _assignment);
    Assignment(int size);

    void resize(int newSize);

    int size() const;
    std::vector<bool>::reference operator[](int index);
    std::vector<bool>::const_reference operator[](int index) const;
};
