#ifndef MINHEAP_H
#define MINHEAP_H

#include <utility>

class MinHeap {
public:
    MinHeap(); // Constructor
    ~MinHeap(); // Destructor

    void MinHeapify(int i, int size);
    void Insert(int vertex, int priority);
    std::pair<int, int> Poll();
    bool isEmpty();

private:
    std::pair<int, int>* a;
    int size;
};

#endif // MINHEAP_H
