#ifndef CRITICALNODEINSTANCE_HPP
#define CRITICALNODEINSTANCE_HPP

#ifndef CRITICALNODESOLUTION_HPP
#include "criticalNodeSolution.hpp"
#else
class CriticalNodeSolution;
#endif

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/graph/betweenness_centrality.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <ostream>
#include <string>
#include <utility>
#include <vector>
class CriticalNodeInstance {

private:
    std::vector<std::pair<int, int>> _adjacencyList;
    int _numberNodes, _maxDeleted;
    double _originalBetweenessCentrality;

    std::pair<int, int> parseLine(std::string line);

    typedef boost::adjacency_matrix<boost::undirectedS> UGraph;
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;
    typedef boost::shared_array_property_map<double, boost::property_map<Graph, boost::vertex_index_t>::const_type> CentralityMap;

public:
    CriticalNodeInstance(){};
    ~CriticalNodeInstance()
    {
        _adjacencyList.clear();
    };

    inline std::vector<std::pair<int, int>> getAdjacencyList() const { return _adjacencyList; }
    inline int getNumNodes() const { return _numberNodes; }

    inline int getMaxDeleted() const { return _maxDeleted; }
    inline int setMaxDeleted(const int& maxDeleted) { _maxDeleted = maxDeleted; }

    void readAdjacencyList(char* filename);

    inline double getBetweenessCentrality() const { return _originalBetweenessCentrality; }
    double getBetweenessCentrality(const CriticalNodeSolution& solution) const;

    int getDisconnectedComponents();
    int getDisconnectedComponents(const CriticalNodeSolution& solution);
};

#endif /* CRITICALNODEINSTANCE_HPP */
