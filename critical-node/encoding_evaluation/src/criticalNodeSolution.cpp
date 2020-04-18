#include "criticalNodeSolution.hpp"
#include "criticalNodeInstance.hpp"
#include <vector>

CriticalNodeSolution::CriticalNodeSolution(const CriticalNodeInstance& instance)
{
    _numNodes = instance.getNumNodes();
    _deletedNodes = *new std::vector<bool>(_numNodes, false);
}
