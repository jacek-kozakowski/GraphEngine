//
// Created by Jacek Kozakowski on 01/01/2026.
//

#ifndef GRAPHENGINE_SPATIALGRAPH_H
#define GRAPHENGINE_SPATIALGRAPH_H

#include "graph.h"

struct Position {
  float x, y, z;
};

class SpatialGraph : public Graph {
private:
  Position *position;

public:
  SpatialGraph(int n);
  ~SpatialGraph();

  void printGraph() const;

  void setPosition(int v, float x, float y, float z = 0.0f);
  Position getPosition(int v) const;

  float manhattanHeuristic(int u, int v) const;
  float euclidianHeuristic(int u, int v) const;
};

#endif // GRAPHENGINE_SPATIALGRAPH_H
