//
// Created by Jacek Kozakowski on 28/12/2025.
//

#ifndef GRAPHENGINE_ALGORITHMS_H
#define GRAPHENGINE_ALGORITHMS_H

#include "graph.h"
#include "spatialgraph.h"
class Algorithms {
private:
  static float heuristic(const SpatialGraph &graph, int u, int v,
                         int heuristic_type);

public:
  static void BFS(const Graph &graph, int start = 0);
  static void DFS(const Graph &graph, int start = 0);
  static void bellmanford(const Graph &graph, int start = 0);
  static void dijkstra(const Graph &graph, int start = 0);
  static void prim(const Graph &graph, int start = 0);
  static void kruskal(const Graph &graph, int start = 0);
  static void astar(const SpatialGraph &graph, int start, int goal,
                    int heuristic_type = 0);
};

#endif // GRAPHENGINE_ALGORITHMS_H
