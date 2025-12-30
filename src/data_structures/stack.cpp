//
// Created by Jacek Kozakowski on 28/12/2025.
//

#include "stack.h"

Stack::Stack(int capacity) : top(0), capacity(capacity) {
    data = new int[capacity];
}

Stack::~Stack(){
    delete data;
}

void Stack::push(int x) {
    data[++top] = x;
}

int Stack::peek() {
    return data[top];
}

int Stack::pop() {
    return data[top--];
}
bool Stack::empty() {
    return top == 0;
}