#include "tester.h"

void integersBubble(void *elements, int first, int second) {
    int *array = (int*) elements;
    if (array[first] > array[second]) {
        swap(array[first], array[second]);
    }
}

void integersSelect(void *elements, int minim, int first) {
    int *array = (int*) elements;
    swap(array[minim], array[first]);
}

void integersInsert(void *elements, int index_01, int useless_var) {
    int *array = (int*) elements;
    int temp_value = array[index_01];
    int j = index_01 - 1;
    while(j>= 0 && array[j] > temp_value) {
        array[j+1] = array[j];
        j -= 1;
    }
    array[j + 1] = temp_value;
}

void integersShell(void *elements, int gap, int index) {
    int *array = (int*) elements;
    int temp = array[index];
    int j;
    for (j = index; j >= gap && array[j-gap] > temp; j-= gap) {
        array[j] = array[j-gap];
    }
    array[j] = temp;
}

void integersQuick(void *elements, int first, int last) {
    int *array = (int*) elements;
    int i = first;
    int j = last;
    int x = array[(first+last)/2];

    do
    {
        while((array[i] < x) && (j <= last))
            i++;

        while((x < array[j]) && (j > first))
            j--;

        if (i <= j)
        {
            swap(array[i], array[j]);
            i++;
            j--;
        }
    } while (i <= j);

    if (first < j)
        integersQuick(array, first, j);

    if (i < last)
        integersQuick(array, i, last);
}


void integersMerge(void *elements, int first, int last) {
    int *array = (int*) elements;

    int mid;
    if (first < last)
    {
        mid = (first + last) / 2;
        integersMerge(elements, first, mid);
        integersMerge(elements, mid + 1, last);
        int *temp = new int[last-first+1];
        int i = first;
        int j = mid + 1;
        int k = 0;
        while(i <= mid && j <= last){
        if(array[i] <= array[j])
          temp[k++] = array[i++];
        else
          temp[k++] = array[j++];
        }

        while(i <= mid)
        temp[k++] = array[i++];

        while(j <= last)
        temp[k++] = array[j++];

        for(k = 0, i = first; i <= last; ++i, ++k)
        array[i] = temp[k];

        delete []temp;
    }
}


Sort* Tester::getSort(Algorithm sort, void *array, size_t size) {
    switch (sort) {
        case bubblesort: return new BubbleSort(array, size);
        case selectsort: return new SelectSort(array, size);
        case insertsort: return new InsertSort(array, size);
        case shellsort: return new ShellSort(array, size);
        case quicksort: return new QuickSort(array, size);
        case mergesort: return new MergeSort(array, size);
        default: throw invalid_argument("Not a valid sort");
    }
}

fptr Tester::getCompare(Algorithm sort) {
    switch (sort) {
        case bubblesort: return &integersBubble;
        case selectsort: return &integersSelect;
        case insertsort: return &integersInsert;
        case shellsort: return &integersShell;
        case quicksort: return &integersQuick;
        case mergesort: return &integersMerge;
        default: throw invalid_argument("Not a valid comparer");
    }
}

void Tester::integerSorts(int *array, size_t size) {
    Sort* sort;
    int temp[size];

    Algorithm algorithm[] = { bubblesort, selectsort, insertsort, shellsort, quicksort, mergesort };
    size_t numberOfAlgorithms = sizeof(algorithm) / sizeof(algorithm[0]);

    for (int i = 0; i < numberOfAlgorithms; i++) {
        copy(array, array + size, temp);
        sort = getSort(algorithm[i], temp, size);
        sort->execute(getCompare(algorithm[i]));
        ASSERT(is_sorted(temp, temp + size), "The " + sort->name() + " is not ordering all the elements");
    }
}
