//
// Created by Jacek Kozakowski on 30/12/2025.
//

#include "DSU.h"

DSU::DSU(int size) :n(size){
    parent = new int[n];
    rank = new int[n]();
    for (int i = 0; i < n; i++) parent[i] =i;
}
DSU::~DSU(){
    delete[] parent;
    delete[] rank;
}

int DSU::find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void DSU::unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;

    if (rank[x] < rank[y]) parent[x] = y;
    else if(rank[x] > rank[y]) parent[y] = x;
    else{
        parent[y] = x;
        rank[x]++;
    }
}
