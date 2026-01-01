//
// Created by Jacek Kozakowski on 28/12/2025.
//

#include "../include/graph.h"

#include <iostream>

Graph::Graph(int n) : n(n) {
    vertices = new Vertex[n];
    for (int i = 0; i < n; i++){
        vertices[i].head = nullptr;
    }
}

Graph::~Graph(){
    for (int i = 0; i < n; i++){
        Edge* e = vertices[i].head;
        while(e){
            Edge* temp = e;
            e = e->next;
            delete temp;
        }
    }
    delete[] vertices;
}

void Graph::addEdge(int u, int v, int w) {
    Edge* e = new Edge();
    e->to = v;
    e->weight = w;
    e->next = vertices[u].head;
    vertices[u].head = e;
}

int Graph::size() const {
    return n;
}

Vertex* Graph::getVertices() const{
    return vertices;
}

void Graph::printGraph() const {
    std::cout << "Graph edges: \n";
    for (int i = 0; i < n; i++) {
        Edge* e = vertices[i].head;
        while(e) {
            std::cout << i <<"->" << e->to << ", w: " << e->weight << std::endl;
            e = e->next;
        }
    }
}
