#include <vector>

class Clause
{
 private:
  std::vector<bool> p;
  std::vector<bool> n;

 public:
  Clause(int size);

  int size() const;
  void set(int var, bool value = true);
  bool get(int var) const;
};
