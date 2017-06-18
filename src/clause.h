#include <vector>

#include "assignment.h"

class Clause
{
private:
    std::vector<int> vars;
    int myWeight;

    bool mySat;

public:
    Clause();
    int size() const;
    //1:+, 0:-
    void set(int var, bool pos);
    void unset(int var, bool pos);
    bool get(int var, bool pos) const;

    std::vector<int> getVariables();
    void setWeight(int weight);
    int getWeight() const;

    bool updateSat(const Assignment &assignment);
    bool isSatisfiable() const;

    int getScore(int flipedVar, const Assignment &assignment);
};
