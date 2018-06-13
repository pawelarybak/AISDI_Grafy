#ifndef IZOMORFIZMY_GRAPH_H
#define IZOMORFIZMY_GRAPH_H

#include <set>
#include <map>
#include <iostream>
#include <fstream>
#include "Edge.h"

template <typename T> class Graph {
public:

    static Graph fromStream(std::fstream& stream) {
        Graph graph;
        int valA;
        int valB;

        stream >> graph.verticesCount;
        while (stream >> valA >> valB) {
            graph.edges.insert(Edge<T>(valA, valB));
        }

        return graph;
    }

    Graph applyFunction(std::map<T, T> mapping) {
        Graph newGraph;
        newGraph.verticesCount = verticesCount;
        for (auto& edge : edges) {
            newGraph.edges.insert(Edge<T>(mapping[edge.first()], mapping[edge.second()]));
        }

        return newGraph;
    }

    size_t vertices() const {
        return verticesCount;
    }

    size_t edgesNum() const {
        return edges.size();
    }

    std::vector<size_t> degrees() const {
        std::map<T, size_t> deg;
        for (auto& edge : edges) {
            deg[edge.first()]++;
            deg[edge.second()]++;
        }
        std::vector<size_t> values;
        for (auto& entry: deg) {
            values.push_back(entry.second);
        }
        return values;
    }

    void print() {
        std::cout << "Size: " << verticesCount << std::endl;
        for (auto& edge : edges) {
            std::cout << edge << std::endl;
        }
    }

    bool operator==(const Graph& other) const {
        return edges == other.edges;
    }

    bool operator!=(const Graph& other) const {
        return !operator==(other);
    }

private:
    std::set<Edge<T>> edges;
    size_t verticesCount;
};

#endif //IZOMORFIZMY_GRAPH_H
