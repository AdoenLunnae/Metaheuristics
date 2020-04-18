#ifndef RANDOMSOLUTIONGENERATOR_HPP
#define RANDOMSOLUTIONGENERATOR_HPP

#include "criticalNodeInstance.hpp"
#include "criticalNodeSolution.hpp"
#include "criticalNodeSolutionGenerator.hpp"

class RandomSolutionGenerator : public CriticalNodeSolutionGenerator {

public:
    CriticalNodeSolution& generate(const CriticalNodeInstance& instance) const;
};

#endif /* RANDOMSOLUTIONGENERATOR_HPP */
