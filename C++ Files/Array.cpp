#include "Array.h"
#include <cstdlib>

Array::Array(int initialSize) {
    arraySize = 0;
    capacity = initialSize;
    array = new int[capacity];
}

Array::~Array() {
    delete[] array;
}

void Array::Clear() {
    delete[] array;
    array = new int[capacity];
    arraySize = 0;
}

void Array::Insert(int x) {
    // Double the size if size of array reaches capacity
    if (arraySize == capacity) {
        capacity *= 2;
        int* newArray = new int[capacity];
        for (int i = 0; i < arraySize; i++) {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
    }
    array[arraySize++] = x;
}

int Array::GetElement(int index) const {
    if (index >= 0 && index < arraySize) {
        return array[index];
    } else {
        return -1;
    }
}
