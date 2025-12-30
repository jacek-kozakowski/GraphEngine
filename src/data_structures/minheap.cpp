//
// Created by Jacek Kozakowski on 29/12/2025.
//

#include "minheap.h"


MinHeap::MinHeap(int cap) : capacity(cap), size(0){
    data = new HeapNode[cap];
    pos = new int[cap];

    for (int i = 0; i < cap; i++ )
        pos[i] = -1;
}

MinHeap::~MinHeap(){
    delete[] data;
    delete[] pos;
}

void MinHeap::insert(int v, int distance) {
    if (pos[v] != -1) return;

    int i = size;
    data[i].vertex = v;
    data[i].distance = distance;
    pos[v] = i;
    size++;
    heapifyUp(i);
}

void MinHeap::heapifyUp(int i) {
    while (i > 0){
        int parent = (i - 1) / 2;
        if (data[parent].distance <= data[i].distance)
            break;

        HeapNode temp = data[i];
        data[i] = data[parent];
        data[parent] = temp;

        pos[data[i].vertex] = parent;
        pos[data[parent].vertex] = i;

        i = parent;
    }
}

void MinHeap::heapifyDown(int i) {
    while(true){
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && data[left].distance < data[smallest].distance)
            smallest = left;
        if (right < size && data[right].distance < data[smallest].distance)
            smallest = right;

        if (smallest == i)
            break;

        HeapNode temp = data[i];
        data[i] = data[smallest];
        data[smallest] = temp;

        pos[data[i].vertex] = smallest;
        pos[data[smallest].vertex] = i;

        i = smallest;
    }
}

HeapNode MinHeap::extractMin() {
    HeapNode min = data[0];

    HeapNode last = data[size - 1];
    data[0] = last;
    pos[last.vertex] = 0;

    pos[min.vertex] = -1;
    size--;

    heapifyDown(0);
    return min;
}

void MinHeap::decreaseKey(int v, int newDistance) {
    int i = pos[v];
    if (i == -1) return;

    if (data[i].distance <= newDistance)
        return;

    data[i].distance = newDistance;
    heapifyUp(i);
}

bool MinHeap::empty() const {
    return size == 0;
}

bool MinHeap::contains(int u) const {
    return pos[u] != -1;
}