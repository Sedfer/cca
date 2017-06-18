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
    int findAverageWeight();

    int size() const;
    Clause* operator[](int index) const;
    std::vector<Clause *>::const_iterator begin() const;
    std::vector<Clause *>::const_iterator end() const;

    bool check(const Assignment &assignment) const;
};
