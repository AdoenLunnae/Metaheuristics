#include "randomSolutionGenerator.hpp"
#include "criticalNodeInstance.hpp"
#include "criticalNodeSolution.hpp"
#include <cstdio>
#include <ctime>

CriticalNodeSolution& RandomSolutionGenerator::generate(const CriticalNodeInstance& instance) const
{
    CriticalNodeSolution* sol = new CriticalNodeSolution(instance);
    int numDeleted = instance.getMaxDeleted();
    int remaining = numDeleted;
    while (remaining > 0) {
        int pos = rand() % instance.getNumNodes();
        if (!sol->isDeleted(pos)) {
            sol->deleteNode(pos);
            remaining--;
        }
    }
    return *sol;
}