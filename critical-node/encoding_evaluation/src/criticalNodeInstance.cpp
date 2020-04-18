#include "criticalNodeInstance.hpp"
#include "criticalNodeSolution.hpp"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/betweenness_centrality.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::pair<int, int> CriticalNodeInstance::parseLine(std::string line)
{
    uint index = line.find(',');
    std::pair<int, int> edge(atoi(line.substr(0, index).c_str()), atoi(line.substr(index + 1).c_str()));
    return edge;
}

void CriticalNodeInstance::readAdjacencyList(char* filename)
{
    std::ifstream f(filename, std::ios::in);
    std::string line;
    std::pair<int, int> nextPair;

    _adjacencyList.clear();

    std::getline(f, line);
    _numberNodes = atoi(line.c_str());
    while (std::getline(f, line)) {
        _adjacencyList.push_back(parseLine(line));
    }
    f.close();

    Graph g(_numberNodes);

    for (auto i = 0; i < _adjacencyList.size(); ++i)
        boost::add_edge(_adjacencyList[i].first, _adjacencyList[i].second, g);

    CentralityMap centralityMap(boost::num_vertices(g), get(boost::vertex_index, g));

    boost::brandes_betweenness_centrality<Graph, CentralityMap>(g, centralityMap);

    double centrality = 0;
    for (int i = 0; i < _numberNodes; ++i) {
        centrality += centralityMap[i]; /// _numberNodes;
    }
    _originalBetweenessCentrality = centrality;
}

double CriticalNodeInstance::getBetweenessCentrality(const CriticalNodeSolution& sol) const
{
    std::vector<std::pair<int, int>> solutionEdges;
    Graph g;
    for (auto i = 0; i < _adjacencyList.size(); ++i) {
        if (!(sol.isDeleted(_adjacencyList[i].first) || sol.isDeleted(_adjacencyList[i].second))) {
            solutionEdges.push_back(_adjacencyList[i]);
            boost::add_edge(_adjacencyList[i].first, _adjacencyList[i].second, g);
        }
    }

    CentralityMap centralityMap(boost::num_vertices(g), get(boost::vertex_index, g));

    boost::brandes_betweenness_centrality<Graph, CentralityMap>(g, centralityMap);

    double centrality = 0;
    for (int i = 0; i < boost::num_vertices(g); ++i)
        centrality += centralityMap[i];

    return centrality;
}

/*

    std::vector<int> component(boost::num_vertices(g), 0);
    int num = boost::connected_components(g, &component[0]);
    component = *new std::vector<int>(component.begin() + 1, component.end());
    std::vector<int>::size_type i;
    std::cout << "Total number of components: " << num << '\n';
    for (i = 0; i < component.size(); ++i)
        std::cout << "Vertex " << i << " is in component " << component[i] << '\n';
*/