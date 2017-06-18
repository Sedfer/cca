#include <vector>
#include <fstream>

#include "clause.h"
#include "assignment.h"
#include "variable.h"

class Formula
{
private:
    std::vector<Clause *> myVector;

    std::vector<Variable *> myVariables;
    Assignment myAssignment;

    void initNeighboursAndClauses();
    void updateScores();
    void updateScore(Variable &var);

public:
    Formula();
    ~Formula();

    void add(Clause *c);

    void init(int vars);

    int size() const;
    Clause* operator[](int index) const;
    std::vector<Clause *>::const_iterator begin() const;
    std::vector<Clause *>::const_iterator end() const;

    Assignment& getAssignment();
    const Assignment &getAssignment() const;

    std::vector<Variable *>& getVariables();
    const std::vector<Variable *>& getVariables() const;

    int findAverageWeight();

    bool check() const;

    void flipVar(int varIndex);
    void updateWeights();
};
