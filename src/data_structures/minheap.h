//
// Created by Jacek Kozakowski on 29/12/2025.
//

#ifndef GRAPHENGINE_MINHEAP_H
#define GRAPHENGINE_MINHEAP_H

template <typename T>
struct HeapNode{
    int vertex;
    T distance;
};
template<typename T>
class MinHeap {
private:
    HeapNode<T>* data;
    int* pos;
    int size;
    int capacity;

    void swap(int i, int j) {
        HeapNode<T> tmp = data[i];
        data[i] = data[j];
        data[j] = tmp;
        pos[data[i].vertex] = i;
        pos[data[j].vertex] = j;
    }

    void heapifyUp(int i) {
        while (i > 0) {
            int p = (i - 1) / 2;
            if (data[p].distance <= data[i].distance) break;
            swap(p, i);
            i = p;
        }
    }

    void heapifyDown(int i) {
        while (true) {
            int l = 2*i + 1;
            int r = 2*i + 2;
            int smallest = i;

            if (l < size && data[l].distance < data[smallest].distance)
                smallest = l;
            if (r < size && data[r].distance < data[smallest].distance)
                smallest = r;

            if (smallest == i) break;
            swap(i, smallest);
            i = smallest;
        }
    }

public:
    MinHeap(int cap) : size(0), capacity(cap) {
        data = new HeapNode<T>[cap];
        pos = new int[cap];
        for (int i = 0; i < cap; i++)
            pos[i] = -1;
    }

    ~MinHeap() {
        delete[] data;
        delete[] pos;
    }

    bool empty() const {
        return size == 0;
    }

    bool contains(int v) const {
        return pos[v] != -1;
    }

    void insert(int v, T distance) {
        if (pos[v] != -1) return;

        int i = size++;
        data[i].vertex = v;
        data[i].distance = distance;
        pos[v] = i;
        heapifyUp(i);
    }

    HeapNode<T> extractMin() {
        HeapNode<T> root = data[0];
        swap(0, --size);
        pos[root.vertex] = -1;
        heapifyDown(0);
        return root;
    }

    void decreaseKey(int v, T newDist) {
        int i = pos[v];
        if (i == -1) return;
        data[i].distance = newDist;
    heapifyUp(i);
    }
};


#endif //GRAPHENGINE_MINHEAP_H
