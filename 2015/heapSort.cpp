// Build a Heap and HeapSort an input array
// http://geeksquiz.com/heap-sort/

#include "utility.h"

struct MinHeap {
    int size;
    vector<int> arr;
};

void printHeap(MinHeap* h) {
    cout << "Heap : "; 
    printArray(h->arr);
}

void upHeap(vector<int> &arr, int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && arr.at(parent) > arr.at(index)) {
        //cout << "\t\tParent = " << arr[parent] << " and Index = " << arr[index] << "\n";
        swap(arr, index, parent);
        index = parent;
        parent = (index - 1) / 2;
    }
}

MinHeap* buildHeap(const vector<int> A) {
    MinHeap* heap = new MinHeap;
    heap->arr = A;
    heap->size = heap->arr.size();
    //cout << "Init heap with size : " << heap->size << "\n";
    //cout << "Heap : "; printArray(heap->arr);
    for (int i=(heap->size - 1); i > 0; i--) {
        //cout << "\tUpheap element : " << heap->arr.at(i) << "\n";
        upHeap(heap->arr, i);
    }
    return heap;
}

int getTop(MinHeap *h) {
    if (h == NULL || h->size < 1) exit(3);
    return h->arr[0];
}

void downHeap(MinHeap *h) {
    int index = 0;
    int size = h->size;
    vector<int>& a = h->arr;
    a[0] = a[size - 1];
    size--; 
    int c1 = 2 * index + 1;
    int c2 = 2 * index + 2;
    while( c1 < size || c2 < size ) {
        //cout << "DownHeap : index = " << index << " c1 = " << c1 << " c2 = " << c2 << "\n";
        //cout << "[downHeap:Enter] "; printHeap(h);
        if ( a.at(c1) < a.at(index) && a.at(c1) < a.at(c2) ) {
            upHeap(a, c1);
            index = c1;
            //cout << "[downHeap:Exit] "; printHeap(h);
        } else if (a.at(c2) < a.at(index) && a.at(c2) < a.at(c1) ) {
            upHeap(a, c2);
            index = c2;
            //cout << "[downHeap:Exit] "; printHeap(h);
        } else {
            break;
        }
        c1 = 2 * index + 1;
        c2 = 2 * index + 2;
    }
}

void pop(MinHeap *h) {
    downHeap(h);
    h->arr.resize(h->size - 1);
    h->size--;
    //cout << "Popped top from heap, size = " << h->size << "\n";
    if (h->size != h->arr.size()) exit(2);
}

vector<int> heapSort(MinHeap* h) {
    vector<int> A;
    while(h->size > 0) {
        A.push_back(getTop(h));
        //cout << "Push : " << getTop(h) << " into sorted array and call pop()\n";
        pop(h);
        //printHeap(h);
    }
    return A;
}

int main() {
    srand(time(NULL));
    
    vector<int> A; 
    generateRandomArray(A, 15);
    printArray(A);
    
    MinHeap *heap = buildHeap(A);
    printHeap(heap);
    
    vector<int> sorted = heapSort(heap);
    cout << "Heap Sorted : "; printArray(sorted);
}
