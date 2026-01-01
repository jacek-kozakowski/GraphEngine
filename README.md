# Graph Engine

Graph Engine is an efficient C++ library designed for graph operations, featuring fundamental search and optimization algorithms along with custom-built data structures.

Graphs are represented using an adjacency list for efficient memory usage and traversal.

## Features

- **Graph Algorithms:**
  - **BFS & DFS:** Basic traversal algorithms.
  - **Dijkstra & Bellman-Ford:** Shortest path algorithms (Bellman-Ford supports negative weights).
  - **Prim & Kruskal:** Minimum Spanning Tree (MST) algorithms.
  - **A\* Search:** Heuristic-based shortest path for spatial graphs.
- **Custom Data Structures:**
  - Implementation of `Queue`, `Stack`, `MinHeap`, and `DSU`.
- **Interactive TUI:**
  - A clean, terminal-based interface with automatic screen clearing and state management.
- **IO System:** Support for loading standard and spatial graphs from comma-separated or space-separated files.

## Compilation

To compile the project, use:
```bash
g++ -std=c++14 main.cpp src/impl/*.cpp src/data_structures/*.cpp -Isrc -o graphengine
```

## Example Graphs

To load your own files, follow the patterns described below. You can find examples in the `graph_files/` directory.

### Standard Graph (`graph.txt`)
The first line contains the number of nodes. Each subsequent line represents an edge.
```
[number_of_nodes]
[u],[v],[weight]
...
```
*Example:*
```
3
0,1,10
1,2,5
```

### Spatial Graph (`spatial_graph.txt`)
The first line contains the number of nodes. The next $N$ lines define vertex coordinates, followed by edge definitions.
```
[number_of_nodes]
[node_id] [x] [y] [z]
...
[u],[v],[weight]
...
```
*Example:*
```
2
0 0.0 0.0 0.0
1 1.0 1.0 0.0
0,1,5
```
