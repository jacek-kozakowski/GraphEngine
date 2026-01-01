# Graph Engine

Graph Engine is an efficient C++ library designed for graph operations, featuring fundamental search and optimization algorithms along with custom-built data structures.

Graphs are represented using an adjacency list for efficient memory usage and traversal.

## Features

- **Graph Algorithms:**
  - **BFS & DFS:** Basic traversal algorithms.
  - **Dijkstra & Bellman-Ford:** Shortest path algorithms (Bellman-Ford supports negative weights).
  - **Prim & Kruskal:** Minimum Spanning Tree (MST) algorithms.
  - **A* Search:** Heuristic-based shortest path for spatial graphs.
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

