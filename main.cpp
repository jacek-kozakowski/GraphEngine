#include "src/include/BST.h"
#include "src/include/algorithms.h"
#include "src/include/graph.h"
#include "src/include/io.h"
#include <iostream>
#include <sstream>
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
  BST bst;
  int categoryChoice = 0;

  while (true) {
    printHeader("GRAPH ENGINE - CATEGORY SELECTION");
    std::cout << " 1. Graphs (Algorithms & IO)\n";
    std::cout << " 2. Trees (BST Operations)\n";
    std::cout << " 3. Quit\n";
    std::cout << "\nCategory choice: ";

    if (!(std::cin >> categoryChoice)) {
      std::cin.clear();
      std::cin.ignore(1000, '\n');
      continue;
    }

    if (categoryChoice == 3)
      break;

    if (categoryChoice == 1) { // GRAPH MENU
      bool backToMain = false;
      while (!backToMain) {
        printHeader("GRAPH ALGORITHMS");
        if (currentGraph)
          std::cout << Color::GREEN << "  [STATUS] Graph ("
                    << currentGraph->size() << " nodes)\n"
                    << Color::RESET;
        else if (currentSpatialGraph)
          std::cout << Color::GREEN << "  [STATUS] Spatial ("
                    << currentSpatialGraph->size() << " nodes)\n"
                    << Color::RESET;
        else
          std::cout << Color::RED << "  [STATUS] No graph loaded\n"
                    << Color::RESET;

        std::cout << "\n 1. Load Graph from file\n";
        std::cout << " 2. Print Current Graph\n";
        std::cout << " 3. Search (BFS/DFS)\n";
        std::cout << " 4. MST (Prim/Kruskal)\n";
        std::cout << " 5. Shortest Path (Dijkstra/Bellman-Ford)\n";
        std::cout << " 6. A* (Spatial only)\n";
        std::cout << " 7. Max Flow (Edmonds-Karp)\n";
        std::cout << " 8. Back to Main Menu\n";
        std::cout << "\nChoice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
          printHeader("LOAD GRAPH");
          std::cout << " 1. Standard\n 2. Spatial\n Choice: ";
          int type;
          std::cin >> type;
          std::cout << "\n 1. Undirected\n 2. Directed\n Choice: ";
          int dir;
          std::cin >> dir;
          bool isDirected = (dir == 2);
          std::cout << "\n Filename: ";
          std::string fn;
          std::cin >> fn;

          delete currentGraph;
          currentGraph = nullptr;
          delete currentSpatialGraph;
          currentSpatialGraph = nullptr;

          if (type == 1)
            currentGraph = IO::loadGraphFromFile(fn, isDirected);
          else
            currentSpatialGraph = IO::loadSpatialGraphFromFile(fn, isDirected);

          if (!currentGraph && !currentSpatialGraph) {
            std::cout << Color::RED << " Loading failed!\n" << Color::RESET;
            waitForEnter();
          }
          break;
        }
        case 2:
          if (!currentGraph && !currentSpatialGraph) {
            std::cout << "Load graph first!";
          } else {
            if (currentGraph)
              currentGraph->printGraph();
            else
              currentSpatialGraph->printGraph();
          }
          waitForEnter();
          break;
        case 3: {
          if (!currentGraph && !currentSpatialGraph) {
            std::cout << "Load graph first!";
          } else {
            std::cout << " 1. BFS\n 2. DFS\n Choice: ";
            int alg, start;
            std::cin >> alg;
            std::cout << " Start index: ";
            std::cin >> start;
            const Graph &g =
                currentGraph ? *currentGraph : *currentSpatialGraph;
            if (alg == 1)
              Algorithms::BFS(g, start);
            else
              Algorithms::DFS(g, start);
          }
          waitForEnter();
          break;
        }
        case 4: {
          if (!currentGraph && !currentSpatialGraph) {
            std::cout << "Load graph first!";
          } else {
            std::cout << " 1. Prim\n 2. Kruskal\n Choice: ";
            int alg;
            std::cin >> alg;
            const Graph &g =
                currentGraph ? *currentGraph : *currentSpatialGraph;
            if (alg == 1)
              Algorithms::prim(g, 0);
            else
              Algorithms::kruskal(g, 0);
          }
          waitForEnter();
          break;
        }
        case 5: {
          if (!currentGraph && !currentSpatialGraph) {
            std::cout << "Load graph first!";
          } else {
            std::cout << " 1. Dijkstra\n 2. Bellman-Ford\n Choice: ";
            int alg, start;
            std::cin >> alg;
            std::cout << " Start: ";
            std::cin >> start;
            const Graph &g =
                currentGraph ? *currentGraph : *currentSpatialGraph;
            if (alg == 1)
              Algorithms::dijkstra(g, start);
            else
              Algorithms::bellmanford(g, start);
          }
          waitForEnter();
          break;
        }
        case 6: {
          if (!currentSpatialGraph) {
            std::cout << "Requires Spatial Graph!";
          } else {
            int start, goal;
            std::cout << " Start: ";
            std::cin >> start;
            std::cout << " Goal: ";
            std::cin >> goal;
            Algorithms::astar(*currentSpatialGraph, start, goal, 0);
          }
          waitForEnter();
          break;
        }
        case 7: {
          if (!currentGraph && !currentSpatialGraph) {
            std::cout << "Load graph first!";
          } else {
            int src, snk;
            std::cout << " Source: ";
            std::cin >> src;
            std::cout << " Sink: ";
            std::cin >> snk;
            const Graph &g =
                currentGraph ? *currentGraph : *currentSpatialGraph;
            Algorithms::edmondskarp(g, src, snk);
          }
          waitForEnter();
          break;
        }
        case 8:
          backToMain = true;
          break;
        }
      }
    } else if (categoryChoice == 2) { // TREE MENU
      bool backToMain = false;
      while (!backToMain) {
        printHeader("BST OPERATIONS");
        std::cout << " 1. Insert Key(s)\n";
        std::cout << " 2. Remove Key\n";
        std::cout << " 3. Search Key\n";
        std::cout << " 4. Print In-Order\n";
        std::cout << " 5. Print Pre-Order\n";
        std::cout << " 6. Print Post-Order\n";
        std::cout << " 7. Balance Tree (DSW)\n";
        std::cout << " 8. Back to Main Menu\n";
        std::cout << "\nChoice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
          std::cout << " Enter keys to insert separated by spaces (end with "
                       "Enter):\n ";
          std::string line;
          std::cin.ignore(1000, '\n');
          std::getline(std::cin, line);
          std::stringstream ss(line);
          int k;
          int count = 0;
          while (ss >> k) {
            bst.insert(k);
            count++;
          }
          std::cout << " Processed " << count << " entries.\n";
          waitForEnter();
          break;
        }
        case 2: {
          int k;
          std::cout << " Key to remove: ";
          std::cin >> k;
          bst.remove(k);
          waitForEnter();
          break;
        }
        case 3: {
          int k;
          std::cout << " Key to search: ";
          std::cin >> k;
          if (bst.search(k))
            std::cout << "\n [FOUND]";
          else
            std::cout << "\n [NOT FOUND]";
          waitForEnter();
          break;
        }
        case 4:
          std::cout << " In-Order: ";
          bst.traverseInOrder();
          waitForEnter();
          break;
        case 5:
          std::cout << " Pre-Order: ";
          bst.traversePreOrder();
          waitForEnter();
          break;
        case 6:
          std::cout << " Post-Order: ";
          bst.traversePostOrder();
          waitForEnter();
          break;
        case 7:
          std::cout << " Balancing tree using DSW algorithm...\n";
          bst.dsw();
          std::cout << " Tree balanced.\n";
          waitForEnter();
          break;
        case 8:
          backToMain = true;
          break;
        }
      }
    }
  }

  delete currentGraph;
  delete currentSpatialGraph;
  return 0;
}
