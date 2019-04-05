#ifndef SELECT_H
#define SELECT_H

#include "sort.h"
#include <algorithm>

class SelectSort : public Sort {
public:
    SelectSort(void *elements, size_t size) : Sort(elements, size) {}

    void execute(void (*compare)(void*, int, int)) {
        int min_index = 0;
        int *arr = (int*) elements;
        for (int i = 0; i < size - 1; i++) {
            min_index = i;
            for (int j = i+1; j < size; j++) {
                if(arr[j] < arr[min_index] )
                    min_index = j;
            }
            compare(elements, min_index, i);
        }
    }

    inline string name() { return "SelectSort"; }
};

#endif

