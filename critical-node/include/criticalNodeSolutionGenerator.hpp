#ifndef CRITICALNODESOLUTIONGENERATOR_HPP
#define CRITICALNODESOLUTIONGENERATOR_HPP
#include "criticalNodeInstance.hpp"
#include "criticalNodeSolution.hpp"

class CriticalNodeSolutionGenerator {

public:
    virtual CriticalNodeSolution& generate(const CriticalNodeInstance& instance) const = 0;
};

#endif /* CRITICALNODESOLUTIONGENERATOR_HPP */
