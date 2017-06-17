#pragma once

#include <vector>

class Assignment
{
 private:
  std::vector<bool> myVector;

 public:
  Assignment();
  Assignment(int size);

  void resize(int newSize);

  int size() const;
  std::vector<bool>::reference operator[](int index);
  const bool& operator[](int index) const;
};
