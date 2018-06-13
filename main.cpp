#include <iostream>
#include <algorithm>
#include <map>
#include <fstream>
#include "Graph.h"

bool isIsomorphic(Graph<int>& graphOne, Graph<int>& graphTwo, std::map<int, int>& function) {
    if (graphOne.vertices() != graphTwo.vertices()) {
        return false;
    }
    if (graphOne.edgesNum() != graphTwo.edgesNum()) {
        return false;
    }
    auto degOne = graphOne.degrees();
    auto degTwo = graphTwo.degrees();
    if (!std::is_permutation(degOne.begin(), degOne.end(), degTwo.begin())) {
        return false;
    }

    std::vector<int> keys(graphOne.vertices());
    std::vector<int> values(graphOne.vertices());
    std::iota(keys.begin(), keys.end(), 0);
    std::iota(values.begin(), values.end(), 0);

    std::map<int, int> initMapping;
    for (int i = 0; i < keys.size(); ++i) {
        initMapping[keys[i]] = values[i];
    }

    bool solution = false;

    #pragma omp parallel for
    for (auto i = 0; i < keys.size(); ++i) {

        auto mapping = initMapping;
        auto valuesPerm = values;
        std::rotate(valuesPerm.begin(), valuesPerm.begin() + i, valuesPerm.begin() + i + 1);

        // Before permutations (after rotation)
        for (int j = 0; j < valuesPerm.size(); ++j) {
            mapping[j] = valuesPerm[j];
        }
        if (graphOne == graphTwo.applyFunction(mapping)) {
            solution = true;
            function = mapping;
        }
        // Permutations
        while (std::next_permutation(valuesPerm.begin() + 1, valuesPerm.end())) {
            if (solution) {
                break;
            }
            for (int j = 0; j < valuesPerm.size(); ++j) {
                mapping[j] = valuesPerm[j];
            }
            if (graphOne == graphTwo.applyFunction(mapping)) {
                solution = true;
                function = mapping;
            }
        }
    }
    return solution;
};

int help(std::string name) {
    std::cerr << "Usage:" << std::endl;
    std::cerr << name << " [first_graph_file] [second_graph_file]" << std::endl;
    return 1;
}

int main(int argc, char** argv) {

    if (argc != 3) {
        return help(argv[0]);
    }

    std::fstream file(argv[1]);
    Graph<int> graph = Graph<int>::fromStream(file);
    file.close();

    std::fstream file2(argv[2]);
    Graph<int> graph2 = Graph<int>::fromStream(file2);
    file2.close();

    std::map<int, int> solution;
    bool result = isIsomorphic(graph, graph2, solution);

    if (result) {
        std::cout << "Izomorficzne" << std::endl;
        for (auto& val: solution) {
            std::cout << val.first << " --> " << val.second << std::endl;
        }
    }
    else {
        std::cout << "Nieizomorficzne" << std::endl;
    }

}