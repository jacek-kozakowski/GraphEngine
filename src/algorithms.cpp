//
// Created by Jacek Kozakowski on 28/12/2025.
//

#include "algorithms.h"
#include "iostream"
#include "data_structures/queue.h"
#include "data_structures/stack.h"
#include "data_structures/minheap.h"

using std::cout;
using std::endl;


void Algorithms::BFS(const Graph& graph, int start) {
    if (start > graph.size() - 1){
        cout<<"Starting vertex is not in graph!" << endl;
        return;
    }
    int* traverse_order = new int[graph.size()];
    bool* visited = new bool[graph.size()]();
    Queue q(graph.size());

    q.push(start);
    int ord = 0;
    while (!q.empty()){
        int u = q.pop();
        if (visited[u]) continue;

        visited[u] = true;

        traverse_order[ord] = u;

        Edge* e = graph.getVertices()[u].head;
        while(e){
            if (!visited[e->to]) q.push(e->to);
            e = e->next;
        }
        ord++;
    }

    cout<< "BFS traverse order: " << endl;
    for (int i = 0; i < graph.size(); i++){
        cout << traverse_order[i] << " ";
        if (i%20 == 0 && i!=0) cout<<endl;
    }
    cout << endl;

    delete[] traverse_order;
    delete[] visited;

}

void Algorithms::DFS(const Graph &graph, int start) {
    if (start > graph.size() - 1){
        cout << "Starting vertex is not in graph!" << endl;
        return;
    }
    int* traverse_order = new int[graph.size()];
    bool* visited = new bool[graph.size()]();

    Stack s(graph.size());

    int ord = 0;

    s.push(start);
    while(!s.empty()){
        int u = s.pop();
        if (visited[u]) continue;

        traverse_order[ord] = u;
        visited[u] = true;

        Edge* e = graph.getVertices()[u].head;
        while(e){
            if (!visited[e->to]) s.push(e->to);
            e = e->next;
        }
        ord++;
    }

    cout << "DFS traverse order: " << endl;
    for (int i = 0; i < graph.size(); i++){
        cout << traverse_order[i] << " ";
        if (i%20 == 0 && i!=0) cout << endl;
    }
    cout << endl;

    delete[] traverse_order;
    delete[] visited;
}

void Algorithms::Dijkstra(const Graph &graph, int start) {
    int n = graph.size();
    if (start > n - 1){
        cout << "Starting vertex not in graph!" << endl;
        return;
    }

    bool* visited = new bool[n]();
    int* source = new int[n];
    int* dist = new int[n];
    for (int i = 0; i < n; i++)
        dist[i] = INT_MAX;


    MinHeap heap(n);
    heap.insert(start, 0);
    source[start] = -1;

    while(!heap.empty()){
        HeapNode node = heap.extractMin();
        int u = node.vertex;
        if (visited[u]) continue;

        visited[u] = true;
        dist[u] = node.distance;

        Edge* e = graph.getVertices()[u].head;
        while(e){
            int v = e->to;
            int w = e->weight;
            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                source[v] = u;

                if (heap.contains(v))
                    heap.decreaseKey(v, dist[v]);
                else
                    heap.insert(v, dist[v]);
            }

            e = e->next;
        }
    }

    cout << "PATHS: " << endl;
    for (int i = 0; i < n; i++){
        cout << "Vertex " << i << '\n' << "PATH LENGTH: "<< dist[i] <<endl;
        cout << "PATH: "<<endl << i;
        int s = source[i];
        while (s != -1){
            cout <<"<-"<< s;
            s = source[s];
        }
        cout << endl;
    }


    delete[] source;
    delete[] visited;
    delete[] dist;

}

void Algorithms::Prim(const Graph &graph, int start) {
    int n = graph.size();
    if (start > n -1){
        cout << "Starting vertex not in graph!\n";
        return;
    }

    bool* included = new bool[n]();
    int* parent = new int[n];
    int* key = new int[n];
    for (int i = 0; i < n; i++) {
        parent[i] = INT_MAX;
        key[i] = INT_MAX;
    }

    MinHeap heap(n);

    heap.insert(start, 0);
    parent[start] = -1;
    key[start] = 0;


    while(!heap.empty()){
        HeapNode node = heap.extractMin();
        int u = node.vertex;

        if (included[u]) continue;
        included[u] = true;

        Edge* e = graph.getVertices()[u].head;

        while(e){
            int v = e->to;
            int w = e->weight;
            if(!included[v] &&  w < key[v]){
                key[v] = w;
                parent[v] = u;
                if (heap.contains(v))
                    heap.decreaseKey(v, w);
                else
                    heap.insert(v, w);
            }
            e = e->next;
        }
    }

    cout << "MST edges:\n";
    int total = 0;
    for (int v = 0; v < n; v++) {
        if (parent[v] != -1) {
            cout << parent[v] << " - " << v << " (w=" << key[v] << ")\n";
            total += key[v];
        }
    }
    cout << "Total weight = " << total << endl;

    delete[] included;
    delete[] parent;
    delete[] key;
}
