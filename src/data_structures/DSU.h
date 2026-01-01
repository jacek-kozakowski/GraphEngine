//
// Created by Jacek Kozakowski on 30/12/2025.
//

#ifndef GRAPHENGINE_DSU_H
#define GRAPHENGINE_DSU_H

struct EdgeInfo{
    int u, v, w;
};

class DSU {
private:
    int* parent;
    int* rank;
    int n;
public:
    DSU(int size);
    ~DSU();

    int find(int x);
    void unite(int x, int y);
};


#endif //GRAPHENGINE_DSU_H
