#ifndef ARRAY_H
#define ARRAY_H

class Array {
public:
    int* array; // Dynamic Array
    int arraySize; // Size of Array
    int capacity; // Max Capacity for array

    Array(int initialSize = 10); // Constructor
    ~Array(); // Destructor
    void Clear(); // Empty Array
    void Insert(int x); 
    int GetElement(int index) const;
};

#endif // ARRAY_H
