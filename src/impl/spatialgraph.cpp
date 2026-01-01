//
// Created by Jacek Kozakowski on 01/01/2026.
//

#include "../include/spatialgraph.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <ostream>

SpatialGraph::SpatialGraph(int n) : Graph(n) { position = new Position[n]; }

SpatialGraph::~SpatialGraph() { delete[] position; }

void SpatialGraph::setPosition(int v, float x, float y, float z) {
  position[v].x = x;
  position[v].y = y;
  position[v].z = z;
}

Position SpatialGraph::getPosition(int v) const { return position[v]; }

float SpatialGraph::manhattanHeuristic(int u, int v) const {
  float dx = position[v].x - position[u].x;
  float dy = position[v].y - position[u].y;
  float dz = position[v].z - position[u].z;
  return std::abs(dx) + std::abs(dy) + std::abs(dz);
}

float SpatialGraph::euclidianHeuristic(int u, int v) const {
  float dx = position[v].x - position[u].x;
  float dy = position[v].y - position[u].y;
  float dz = position[v].z - position[u].z;
  return sqrt(dx * dx + dy * dy + dz * dz);
}

void SpatialGraph::printGraph() const {
  std::cout << "Graph: " << std::endl;
  for (int i = 0; i < this->size(); i++) {
    Position p = position[i];
    std::cout << "Vertex " << i << " position: " << p.x << ", " << p.y << ", "
              << p.z << std::endl;
    Edge *e = getVertices()[i].head;
    while (e) {
      std::cout << i << "->" << e->to << ", w: " << e->weight << std::endl;
      e = e->next;
    }
  }
}
