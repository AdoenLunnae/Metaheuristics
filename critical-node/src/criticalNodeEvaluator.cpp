#include "criticalNodeEvaluator.hpp"
#include "criticalNodeInstance.hpp"
#include "criticalNodeSolution.hpp"

double CriticalNodeEvaluator::getFitness(const CriticalNodeInstance& instance, const CriticalNodeSolution& solution)
{
    return (instance.getBetweenessCentrality() - instance.getBetweenessCentrality(solution));
}