//
// Created by Jacek Kozakowski on 29/12/2025.
//

#ifndef GRAPHENGINE_IO_H
#define GRAPHENGINE_IO_H
#include "graph.h"
#include "spatialgraph.h"
#include "string"

class IO {
private:
    static void parseEdge(const char* line, int& u, int& v, int& w);
    static void parseVertex(const char* line, int& u, float& x, float& y, float& z);
public:
    static Graph *loadGraphFromFile(const std::string &filepath, bool directed = true);
    static SpatialGraph *loadSpatialGraphFromFile(const std::string &filepath, bool directed = true);
};


#endif //GRAPHENGINE_IO_H
