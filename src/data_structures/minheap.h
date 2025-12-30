//
// Created by Jacek Kozakowski on 29/12/2025.
//

#ifndef GRAPHENGINE_MINHEAP_H
#define GRAPHENGINE_MINHEAP_H


struct HeapNode{
    int vertex;
    int distance;
};

class MinHeap {
private:
    HeapNode* data;
    int* pos; // pos[v] = index of v in data;
    int size;
    int capacity;

public:
    MinHeap(int cap);
    ~MinHeap();

    HeapNode extractMin();
    void decreaseKey(int v, int newDistance);
    void insert(int v, int distance);
    bool empty() const;
    bool contains(int u) const;

private:
    void heapifyUp(int i);
    void heapifyDown(int i);
};


#endif //GRAPHENGINE_MINHEAP_H
