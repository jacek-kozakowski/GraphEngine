//
// Created by Jacek Kozakowski on 28/12/2025.
//

#ifndef GRAPHENGINE_STACK_H
#define GRAPHENGINE_STACK_H


class Stack {
private:
    int* data;
    int top;
    int capacity;
public:
    Stack(int capacity);
    ~Stack();

    int pop();
    int peek();
    void push(int x);
    bool empty();
};


#endif //GRAPHENGINE_STACK_H
