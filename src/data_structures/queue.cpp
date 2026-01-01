//
// Created by Jacek Kozakowski on 28/12/2025.
//

#include "queue.h"


Queue::Queue(int n) : front(0), back(0), capacity(n) {
    data = new int[n];
}

Queue::~Queue(){
    delete data;
}

void Queue::push(int x) {
    data[back] = x;
    back = (back + 1) % capacity;
}

int Queue::peek() {
    return data[front];
}

int Queue::pop() {
    int val = data[front];
    front = (front + 1) % capacity;
    return val;
}

bool Queue::empty() const{
    return front == back;
}