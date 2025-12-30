//
// Created by Jacek Kozakowski on 28/12/2025.
//

#ifndef GRAPHENGINE_ALGORITHMS_H
#define GRAPHENGINE_ALGORITHMS_H
#include "graph.h"

class Algorithms {
public:
    static void BFS(const Graph& graph, int start = 0);
    static void DFS(const Graph& graph, int start = 0);
    static void Dijkstra(const Graph& graph, int start = 0);
    static void Prim(const Graph& graph, int start = 0);
};


#endif //GRAPHENGINE_ALGORITHMS_H
