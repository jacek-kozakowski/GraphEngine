//
// Created by Jacek Kozakowski on 28/12/2025.
//

#ifndef GRAPHENGINE_GRAPH_H
#define GRAPHENGINE_GRAPH_H

struct Edge {
  int to;
  int weight;
  Edge *next;
};

struct Vertex {
  Edge *head;
};

class Graph {
private:
  int n;
  Vertex *vertices;

public:
  Graph(int n);
  virtual ~Graph();

  void printGraph() const;
  void addEdge(int u, int v, int w = 1);
  int size() const;
  Vertex *getVertices() const;
};

#endif // GRAPHENGINE_GRAPH_H
