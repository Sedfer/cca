#include <vector>

class Clause
{
 private:
  std::vector<bool> p;
  std::vector<bool> n;

  int myWeight;

 public:
  Clause(int size);

  int size() const;
  void set(int var, bool value = true);
  bool get(int var) const;

  void setWeight(int weight);
  int getWeight() const;
};
