#include "MinHeap.h"
#include "Constants.h"
#include <iostream>
#include <climits>

MinHeap::MinHeap() {
    a = new std::pair<int, int>[MAX_VERTICES + 1];
    size = 1;
}

MinHeap::~MinHeap() {
    delete[] a;
}

//Maintain MinHeap Structure
void MinHeap::MinHeapify(int i, int heapSize) {
    int left = 2 * i;
    int right = 2 * i + 1;
    int smallest = i;
    //Compare if left child is smaller than parent
    if (left < heapSize && a[left].first < a[i].first) smallest = left;
    //Compare if right child is smaller than parent
    if (right < heapSize && a[right].first < a[smallest].first) smallest = right;
    //If child is smaller than parent, swap and call function again
    if (smallest != i) {
        swap(a[i], a[smallest]);
        MinHeapify(smallest, heapSize);
    }
}

//Insert Vertex and priority for heap
void MinHeap::Insert(int vertex, int priority) {
    a[size] = {priority, vertex};
    int i = size++; //Compare and swap any vertices with the parent
    while (i > 1 && a[i / 2].first > a[i].first) {
        swap(a[i], a[i / 2]);
        i /= 2;
    }
}

//Return the minimum of two vertices
std::pair<int, int> MinHeap::Poll() {
    //Check if pq is empty and return if true
    if (size == 1) {
        std::cout << "Priority queue is empty." << std::endl;
        return {-1, -1};
    }
    std::pair<int, int> minItem = a[1]; // Create pair minItem "a[1]"
    a[1] = a[--size];
    MinHeapify(1, size); //Perform heapify
    return minItem;
}

bool MinHeap::isEmpty() {
    return size <= 1;
}
