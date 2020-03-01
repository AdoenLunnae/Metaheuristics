#ifndef CRITICALNODEEVALUATOR_HPP
#define CRITICALNODEEVALUATOR_HPP
#include "criticalNodeInstance.hpp"
#include "criticalNodeSolution.hpp"

class CriticalNodeEvaluator {
public:
    static double getFitness(const CriticalNodeInstance& instance, const CriticalNodeSolution& solution);
};
#endif /* CRITICALNODEEVALUATOR_HPP */
