//
// Created by Jacek Kozakowski on 28/12/2025.
//

#ifndef GRAPHENGINE_QUEUE_H
#define GRAPHENGINE_QUEUE_H


class Queue {
private:
    int* data;
    int front;
    int back;
    int capacity;

public:
    Queue(int n);
    ~Queue();

    int pop();
    int peek();
    void push(int x);
    bool empty();
};


#endif //GRAPHENGINE_QUEUE_H
