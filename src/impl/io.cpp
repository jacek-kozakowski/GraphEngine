//
// Created by Jacek Kozakowski on 29/12/2025.
//

#include "../include/io.h"
#include "cstdlib"
#include "fstream"
#include "iostream"
using namespace std;

Graph *IO::loadGraphFromFile(const string &filepath, bool directed) {
  ifstream file(filepath);
  if (!file) {
    cout << "Cannot open file: " << filepath << '\n';
    return nullptr;
  }
  string line;
  getline(file, line);

  int size = strtol(line.c_str(), nullptr, 10);
  Graph *graph = new Graph(size);

  int line_count = 1;

  while (getline(file, line)) {
    int u, v, w;
    parseEdge(line.c_str(), u, v, w);
    graph->addEdge(u, v, w);
    if (!directed) {
      graph->addEdge(v, u, w);
    }
    line_count++;
  }

  file.close();
  cout << "Read " << line_count << " lines.\n";
  return graph;
}

SpatialGraph *IO::loadSpatialGraphFromFile(const std::string &filepath,
                                           bool directed) {
  ifstream file(filepath);
  if (!file) {
    cout << "Cannot open file: " << filepath << '\n';
    return nullptr;
  }
  string line;
  getline(file, line);
  int size = strtol(line.c_str(), nullptr, 10);
  SpatialGraph *graph = new SpatialGraph(size);
  int line_count = 1;
  while (getline(file, line)) {
    if (line_count - 1 < size) {
      if (!line.size())
        break;
      int u;
      float x, y, z;
      parseVertex(line.c_str(), u, x, y, z);
      graph->setPosition(u, x, y, z);
    }else {
      int u, v, w;
      parseEdge(line.c_str(), u, v, w);
      graph->addEdge(u, v, w);
      if (!directed) {
        graph->addEdge(v, u, w);
      }
    }
    line_count++;
  }
  return graph;
}

static void skipDelimiter(const char *&p) {
  while (*p == ' ' || *p == ',')
    p++;
}

void IO::parseEdge(const char *line, int &u, int &v, int &w) {
  const char *p = line;
  u = strtol(p, (char **)&p, 10);
  skipDelimiter(p);
  v = strtol(p, (char **)&p, 10);
  skipDelimiter(p);
  w = strtol(p, (char **)&p, 10);
}

void IO::parseVertex(const char *line, int &u, float &x, float &y, float &z) {
  const char *p = line;
  u = strtol(p, (char **)&p, 10);
  skipDelimiter(p);
  x = strtof(p, (char **)&p);
  skipDelimiter(p);
  y = strtof(p, (char **)&p);
  skipDelimiter(p);
  z = strtof(p, (char **)&p);
}