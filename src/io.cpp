//
// Created by Jacek Kozakowski on 29/12/2025.
//

#include "io.h"
#include "iostream"
#include "fstream"
#include "cstdlib"
using namespace std;

Graph* IO::loadGraphFromFile(const string& filepath, bool directed) {
    ifstream file(filepath);
    if (!file){
        cout << "Cannot open file: " << filepath <<'\n';
        return nullptr;
    }
    string line;
    getline(file, line);

    int size = strtol(line.c_str(), nullptr, 10);
    Graph* graph = new Graph(size);

    int line_count = 1;

    while(getline(file, line)){
        int u,v,w;
        parseEdge(line.c_str(), u, v, w);
        graph->addEdge(u, v, w);
        if (!directed){
            graph->addEdge(v,u,w);
        }
        line_count++;
    }

    file.close();
    cout << "Read " << line_count << " lines.\n";
    return graph;
}

void IO::parseEdge(const char *line, int &u, int &v, int &w) {
    const char* p = line;
    u = strtol(p, (char**)&p, 10);
    p++;
    v = strtol(p, (char**)&p, 10);
    p++;
    w = strtol(p, (char**)&p, 10);
}