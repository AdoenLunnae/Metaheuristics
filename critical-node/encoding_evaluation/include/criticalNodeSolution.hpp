#ifndef CRITICALNODESOLUTION_HPP
#define CRITICALNODESOLUTION_HPP

#ifndef CRITICALNODEINSTANCE_HPP
#include "criticalNodeInstance.hpp"
#else
class CriticalNodeInstance;
#endif

#include <vector>

class CriticalNodeSolution {
private:
    int _numNodes;
    std::vector<bool> _deletedNodes;

public:
    CriticalNodeSolution();

    CriticalNodeSolution(const CriticalNodeInstance& instance);

    CriticalNodeSolution(const int& numNodes, std::vector<bool> deletedNodes)
        : _numNodes(numNodes)
        , _deletedNodes(deletedNodes){};

    ~CriticalNodeSolution(){};

    inline void deleteNode(const int& index) { _deletedNodes[index] = true; }
    inline bool isDeleted(const int& index) const { return _deletedNodes[index]; }
};

#endif /* CRITICALNODESOLUTION_HPP */
