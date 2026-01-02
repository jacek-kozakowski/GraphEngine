#include "src/include/algorithms.h"
#include "src/include/graph.h"
#include "src/include/io.h"
#include <iostream>
#include <string>

namespace Color {
const std::string RESET = "\033[0m";
const std::string BOLD = "\033[1m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN = "\033[36m";
const std::string WHITE = "\033[37m";
const std::string CLEAR_FULL = "\033[2J\033[H\033[3J";
const std::string HIDE_CURSOR = "\033[?25l";
const std::string SHOW_CURSOR = "\033[?25h";
} // namespace Color

void printHeader(const std::string &title) {
  int totalWidth = 72;             // Total width including borders
  int innerWidth = totalWidth - 2; // Width for content and padding

  int leftPadding = (innerWidth - (int)title.length()) / 2;
  int rightPadding = innerWidth - (int)title.length() - leftPadding;

  std::cout << "\033[H\033[2J\033[3J" << Color::SHOW_CURSOR << std::flush;
  std::cout << Color::BOLD << Color::CYAN;
  std::cout << "╔" << std::string(innerWidth, '=') << "╗\n";
  std::cout << "║" << std::string(leftPadding, ' ') << title
            << std::string(rightPadding, ' ') << "║\n";
  std::cout << "╚" << std::string(innerWidth, '=') << "╝\n"
            << Color::RESET << "\n";
}

void waitForEnter() {
  std::cout << "\n"
            << Color::YELLOW << "Press Enter to continue..." << Color::RESET
            << std::flush;
  std::cin.ignore(1000, '\n');
  std::cin.get();
}

int main() {
  Graph *currentGraph = nullptr;
  SpatialGraph *currentSpatialGraph = nullptr;
  int choice = 0;

  while (true) {
    printHeader("GRAPH ENGINE - MAIN MENU");
    if (currentGraph)
      std::cout << Color::GREEN << "  [STATUS] Graph loaded ("
                << currentGraph->size() << " nodes)\n"
                << Color::RESET;
    else if (currentSpatialGraph)
      std::cout << Color::GREEN << "  [STATUS] Spatial Graph loaded ("
                << currentSpatialGraph->size() << " nodes)\n"
                << Color::RESET;
    else
      std::cout << Color::RED << "  [STATUS] No graph loaded\n" << Color::RESET;

    std::cout << "\n 1. Load Graph from file\n";
    std::cout << " 2. Print Current Graph\n";
    std::cout << " 3. Search Algorithms (BFS/DFS)\n";
    std::cout << " 4. MST Algorithms (Prim/Kruskal)\n";
    std::cout << " 5. Shortest Path (Dijkstra/Bellman Ford)\n";
    std::cout << " 6. A* Algorithm (Spatial only)\n";
    std::cout << " 7. Max Flow (Edmonds Karp)\n";
    std::cout << " 8. Quit\n";
    std::cout << "\nChoice: ";

    if (!(std::cin >> choice)) {
      std::cin.clear();
      std::cin.ignore(1000, '\n');
      continue;
    }

    if (choice == 8)
      break;

    switch (choice) {
    case 1: {
      printHeader("LOAD GRAPH");
      std::cout << " 1. Standard Graph\n 2. Spatial Graph\n Choice: ";
      int type;
      std::cin >> type;

      std::cout << "\n 1. Undirected\n 2. Directed\n Choice: ";
      int dirChoice;
      std::cin >> dirChoice;
      bool isDirected = (dirChoice == 2);

      std::cout << "\n Enter filename: ";
      std::string filename;
      std::cin >> filename;

      delete currentGraph;
      currentGraph = nullptr;
      delete currentSpatialGraph;
      currentSpatialGraph = nullptr;

      if (type == 1)
        currentGraph = IO::loadGraphFromFile(filename, isDirected);
      else
        currentSpatialGraph =
            IO::loadSpatialGraphFromFile(filename, isDirected);

      if (!currentGraph && !currentSpatialGraph) {
        std::cout << Color::RED << " Failed to load graph!\n" << Color::RESET;
        waitForEnter();
      }
      break;
    }
    case 2: {
      if (!currentGraph && !currentSpatialGraph) {
        std::cout << "Load a graph first!";
        waitForEnter();
        break;
      }
      printHeader("CURRENT GRAPH STRUCTURE");
      if (currentGraph)
        currentGraph->printGraph();
      else if (currentSpatialGraph)
        currentSpatialGraph->printGraph();
      waitForEnter();
      break;
    }
    case 3: {
      if (!currentGraph && !currentSpatialGraph) {
        std::cout << "Load a graph first!";
        waitForEnter();
        break;
      }
      printHeader("SEARCH ALGORITHMS");
      std::cout << " 1. BFS\n 2. DFS\n Choice: ";
      int alg;
      std::cin >> alg;
      std::cout << " Start node index: ";
      int start;
      std::cin >> start;
      const Graph &g = currentGraph ? *currentGraph : *currentSpatialGraph;
      if (alg == 1)
        Algorithms::BFS(g, start);
      else
        Algorithms::DFS(g, start);
      waitForEnter();
      break;
    }
    case 4: {
      if (!currentGraph && !currentSpatialGraph) {
        std::cout << "Load a graph first!";
        waitForEnter();
        break;
      }
      printHeader("MST ALGORITHMS");
      std::cout << " 1. Prim\n 2. Kruskal\n Choice: ";
      int alg;
      std::cin >> alg;
      const Graph &g = currentGraph ? *currentGraph : *currentSpatialGraph;
      if (alg == 1)
        Algorithms::prim(g, 0);
      else
        Algorithms::kruskal(g, 0);
      waitForEnter();
      break;
    }
    case 5: {
      if (!currentGraph && !currentSpatialGraph) {
        std::cout << "Load a graph first!";
        waitForEnter();
        break;
      }
      printHeader("SHORTEST PATH ALGORITHMS");
      std::cout << " 1. Dijkstra (Positive weights only)\n";
      std::cout << " 2. Bellman-Ford (Allows negative weights)\n";
      std::cout << " Choice: ";
      int alg;
      std::cin >> alg;

      std::cout << "\n Start node index: ";
      int start;
      std::cin >> start;
      const Graph &g = currentGraph ? *currentGraph : *currentSpatialGraph;

      if (alg == 1)
        Algorithms::dijkstra(g, start);
      else
        Algorithms::bellmanford(g, start);

      waitForEnter();
      break;
    }
    case 6: {
      if (!currentSpatialGraph) {
        std::cout << Color::RED << " A* requires a Spatial Graph!\n"
                  << Color::RESET;
        waitForEnter();
        break;
      }
      printHeader("A* ALGORITHM");
      int start, goal;
      std::cout << " Start node: ";
      std::cin >> start;
      std::cout << " Goal node: ";
      std::cin >> goal;
      Algorithms::astar(*currentSpatialGraph, start, goal, 0);
      waitForEnter();
      break;
    }
    case 7: {
      if (!currentGraph && !currentSpatialGraph) {
        std::cout << "Load a graph first!";
        waitForEnter();
        break;
      }
      printHeader("FORD-FULKERSON (MAX FLOW)");
      int source, sink;
      std::cout << " Enter source node index: ";
      std::cin >> source;
      std::cout << " Enter sink node index: ";
      std::cin >> sink;

      const Graph &g = currentGraph ? *currentGraph : *currentSpatialGraph;
      Algorithms::edmondskarp(g, source, sink);

      waitForEnter();
      break;
    }
    }
  }

  delete currentGraph;
  delete currentSpatialGraph;
  return 0;
}
