#include <iostream>
#include "src/graph.h"
#include "src/io.h"
#include "src/algorithms.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: " << argv[0] << " <path_to_graph_file>" << endl;
        return 1;
    }
    
    Graph* g_ptr = IO::loadGraphFromFile(argv[1], false);
    if (!g_ptr) {
        cerr << "Error: Could not load graph from " << argv[1] << endl;
        return 1;
    }
    
    Graph g = *g_ptr;
}