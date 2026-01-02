//
// Created by Jacek Kozakowski on 28/12/2025.
//

#include "../include/algorithms.h"
#include "../data_structures/DSU.h"
#include "../data_structures/minheap.h"
#include "../data_structures/queue.h"
#include "../data_structures/stack.h"
#include "iostream"
#include <algorithm>
#include <climits>

using std::cout;
using std::endl;

void Algorithms::BFS(const Graph &graph, int start) {
  int n = graph.size();
  if (start > n - 1 || start < 0) {
    cout << "Starting vertex is not in graph!" << endl;
    return;
  }
  int *traverse_order = new int[n];
  bool *visited = new bool[n]();
  Queue q(n);

  q.push(start);
  int ord = 0;
  while (!q.empty()) {
    int u = q.pop();
    if (visited[u])
      continue;

    visited[u] = true;

    traverse_order[ord] = u;

    Edge *e = graph.getVertices()[u].head;
    while (e) {
      if (!visited[e->to])
        q.push(e->to);
      e = e->next;
    }
    ord++;
  }

  cout << "BFS traverse order: " << endl;
  for (int i = 0; i < ord; i++) {
    cout << traverse_order[i] << " ";
    if ((i + 1) % 20 == 0)
      cout << endl;
  }
  cout << endl;

  delete[] traverse_order;
  delete[] visited;
}

void Algorithms::DFS(const Graph &graph, int start) {
  int n = graph.size();
  if (start > n - 1 || start < 0) {
    cout << "Starting vertex is not in graph!" << endl;
    return;
  }
  int *traverse_order = new int[n];
  bool *visited = new bool[n]();

  Stack s(n);

  int ord = 0;

  s.push(start);
  while (!s.empty()) {
    int u = s.pop();
    if (visited[u])
      continue;

    traverse_order[ord] = u;
    visited[u] = true;

    Edge *e = graph.getVertices()[u].head;
    while (e) {
      if (!visited[e->to])
        s.push(e->to);
      e = e->next;
    }
    ord++;
  }

  cout << "DFS traverse order: " << endl;
  for (int i = 0; i < ord; i++) {
    cout << traverse_order[i] << " ";
    if ((i + 1) % 20 == 0)
      cout << endl;
  }
  cout << endl;

  delete[] traverse_order;
  delete[] visited;
}

void Algorithms::bellmanford(const Graph &graph, int start) {
  int n = graph.size();
  if (start > n - 1 || start < 0) {
    cout << "Starting vertex is not in graph!" << endl;
    return;
  }
  int *dist = new int[n];
  int *parent = new int[n];
  for (int i = 0; i < n; i++) {
    parent[i] = -1;
    dist[i] = INT_MAX;
  }
  dist[start] = 0;
  for (int i = 0; i < n; i++) {
    for (int u = 0; u < n; u++) {
      Edge *e = graph.getVertices()[u].head;
      while (e) {
        int v = e->to;
        int w = e->weight;
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
          if (i == n - 1) {
            cout << "Negative cycle detected!\n";
            return;
          }
          dist[v] = dist[u] + w;
          parent[v] = u;
        }
        e = e->next;
      }
    }
  }
  cout << "PATHS: \n";
  for (int i = 0; i < n; i++) {
    cout << "Vertex " << i << '\n' << "PATH LENGTH: " << dist[i] << endl;
    cout << "PATH: " << endl << i;
    int s = parent[i];
    while (s != -1) {
      cout << "<-" << s;
      s = parent[s];
    }
    cout << endl;
  }
  delete[] dist;
  delete[] parent;
}

void Algorithms::dijkstra(const Graph &graph, int start) {
  int n = graph.size();
  if (start > n - 1 || start < 0) {
    cout << "Starting vertex not in graph!" << endl;
    return;
  }

  bool *visited = new bool[n]();
  int *parent = new int[n];
  int *dist = new int[n];
  for (int i = 0; i < n; i++) {
    parent[i] = -1;
    dist[i] = INT_MAX;
  }

  MinHeap<int> heap(n);
  heap.insert(start, 0);

  while (!heap.empty()) {
    HeapNode<int> node = heap.extractMin();
    int u = node.vertex;
    if (visited[u])
      continue;

    visited[u] = true;
    dist[u] = node.distance;

    Edge *e = graph.getVertices()[u].head;
    while (e) {
      int v = e->to;
      int w = e->weight;
      if (!visited[v] && dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
        parent[v] = u;

        if (heap.contains(v))
          heap.decreaseKey(v, dist[v]);
        else
          heap.insert(v, dist[v]);
      }

      e = e->next;
    }
  }

  cout << "PATHS: " << endl;
  for (int i = 0; i < n; i++) {
    cout << "Vertex " << i << '\n' << "PATH LENGTH: " << dist[i] << endl;
    cout << "PATH: " << endl << i;
    int s = parent[i];
    while (s != -1) {
      cout << "<-" << s;
      s = parent[s];
    }
    cout << endl;
  }

  delete[] parent;
  delete[] visited;
  delete[] dist;
}

void Algorithms::prim(const Graph &graph, int start) {
  int n = graph.size();
  if (start > n - 1 || start < 0) {
    cout << "Starting vertex not in graph!\n";
    return;
  }

  bool *included = new bool[n]();
  int *parent = new int[n];
  int *key = new int[n];
  for (int i = 0; i < n; i++) {
    parent[i] = INT_MAX;
    key[i] = INT_MAX;
  }

  MinHeap<int> heap(n);

  heap.insert(start, 0);
  parent[start] = -1;
  key[start] = 0;

  while (!heap.empty()) {
    HeapNode<int> node = heap.extractMin();
    int u = node.vertex;

    if (included[u])
      continue;
    included[u] = true;

    Edge *e = graph.getVertices()[u].head;

    while (e) {
      int v = e->to;
      int w = e->weight;
      if (!included[v] && w < key[v]) {
        key[v] = w;
        parent[v] = u;
        if (heap.contains(v))
          heap.decreaseKey(v, w);
        else
          heap.insert(v, w);
      }
      e = e->next;
    }
  }

  cout << "MST edges:\n";
  int total = 0;
  for (int v = 0; v < n; v++) {
    if (parent[v] != -1) {
      cout << parent[v] << " - " << v << " (w=" << key[v] << ")\n";
      total += key[v];
    }
  }
  cout << "Total weight = " << total << endl;

  delete[] included;
  delete[] parent;
  delete[] key;
}

void Algorithms::kruskal(const Graph &graph, int start) {
  int n = graph.size();
  if (start > n - 1 || start < 0) {
    cout << "Starting vertex not in graph!\n";
    return;
  }

  int edge_count = 0;
  for (int u = 0; u < n; u++) {
    Edge *e = graph.getVertices()[u].head;
    while (e) {
      if (u < e->to)
        edge_count++;
      e = e->next;
    }
  }

  EdgeInfo *edges = new EdgeInfo[edge_count];
  int idx = 0;
  for (int u = 0; u < n; u++) {
    Edge *e = graph.getVertices()[u].head;
    while (e) {
      if (u < e->to)
        edges[idx++] = {u, e->to, e->weight};
      e = e->next;
    }
  }

  std::sort(edges, edges + edge_count,
            [](const EdgeInfo &a, const EdgeInfo &b) { return a.w < b.w; });

  DSU dsu(n);

  int total_weight = 0;
  cout << "MST edges: \n";
  for (int i = 0; i < edge_count; i++) {
    int u = edges[i].u;
    int v = edges[i].v;
    int w = edges[i].w;

    if (dsu.find(u) != dsu.find(v)) {
      dsu.unite(u, v);
      cout << u << " - " << v << " (w=" << w << ")\n";
      total_weight += w;
    }
  }
  cout << "Total weight = " << total_weight << endl;
  delete[] edges;
}

void Algorithms::edmondskarp(const Graph &graph, int source, int sink) {
  int n = graph.size();
  if (source > n - 1 || source < 0) {
    cout << "Starting vertex not in graph!\n";
    return;
  }
  if (sink > n - 1 || sink < 0) {
    cout << "Sink vertex not in graph!\n";
    return;
  }
  int **residualCap = new int *[n];
  for (int i = 0; i < n; i++) {
    residualCap[i] = new int[n]();
  }

  for (int u = 0; u < n; u++) {
    Edge *e = graph.getVertices()[u].head;
    while (e) {
      int v = e->to;
      int w = e->weight;
      residualCap[u][v] += w;
      e = e->next;
    }
  }

  int *parent = new int[n];
  int maxFlow = 0;

  while (true) {
    for (int i = 0; i < n; i++)
      parent[i] = -1;

    Queue q(n);
    q.push(source);
    parent[source] = source;
    bool found = false;

    while (!q.empty()) {
      int u = q.pop();

      if (u == sink) {
        found = true;
        break;
      }
      for (int v = 0; v < n; v++) {
        if (parent[v] == -1 && residualCap[u][v] > 0) {
          parent[v] = u;
          q.push(v);
        }
      }
      if (found)
        break;
    }
    if (!found)
      break;

    int pathFlow = INT_MAX;

    for (int v = sink; v != source; v = parent[v]) {
      int u = parent[v];
      if (residualCap[u][v] < pathFlow) {
        pathFlow = residualCap[u][v];
      }
    }
    for (int v = sink; v != source; v = parent[v]) {
      int u = parent[v];
      residualCap[u][v] -= pathFlow;
      residualCap[v][u] += pathFlow;
    }
    maxFlow += pathFlow;
  }
  cout << "Maximum flow: " << maxFlow << endl;

  for (int i = 0; i < n; i++) {
    delete[] residualCap[i];
  }

  delete[] residualCap;
  delete[] parent;
}

void Algorithms::astar(const SpatialGraph &graph, int start, int goal,
                       int heuristic_type) {
  int n = graph.size();
  if (start > n - 1 || start < 0) {
    cout << "Starting vertex not in graph!\n";
    return;
  }
  if (goal > n - 1 || goal < 0) {
    cout << "Goal vertex not in graph!\n";
    return;
  }
  if (heuristic_type > 1 || heuristic_type < 0) {
    cout << "Heuristic type not recognized! Using manhattan heuristic.\n";
  }

  bool *closed = new bool[n]();
  int *g = new int[n];
  int *parent = new int[n];

  for (int i = 0; i < n; i++) {
    parent[i] = -1;
    g[i] = INT_MAX;
  }

  MinHeap<float> heap(n);
  g[start] = 0;
  heap.insert(start, 0);
  while (!heap.empty()) {
    HeapNode<float> node = heap.extractMin();
    int u = node.vertex;
    if (u == goal)
      break;
    if (closed[u])
      continue;
    closed[u] = true;

    Edge *e = graph.getVertices()[u].head;
    while (e) {
      int v = e->to;
      int w = e->weight;

      int tentative_weight = g[u] + w;
      if (tentative_weight < g[v]) {
        g[v] = tentative_weight;
        parent[v] = u;

        float f = g[v] + heuristic(graph, v, goal, heuristic_type);
        if (heap.contains(v))
          heap.decreaseKey(v, f);
        else
          heap.insert(v, f);
      }
      e = e->next;
    }
  }

  cout << "A* PATH: \n";
  for (int v = goal; v != -1; v = parent[v]) {
    if (v == goal)
      cout << v;
    else
      cout << "<-" << v;
  }
  cout << endl;
  cout << "PATH LENGTH: " << g[goal] << endl;

  delete[] closed;
  delete[] g;
  delete[] parent;
}

float Algorithms::heuristic(const SpatialGraph &graph, int u, int v,
                            int heuristic_type) {
  // manhattan
  if (heuristic_type == 0) {
    return graph.manhattanHeuristic(u, v);
  }
  if (heuristic_type == 1) { // euclidian
    return graph.euclidianHeuristic(u, v);
  }
  return graph.manhattanHeuristic(u, v);
}
