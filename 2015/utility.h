#include<iostream>
#include<vector>
#include<stdlib.h>
#include<iomanip>
#include<deque>
#include<math.h>
#include<time.h>
#include<string>

using namespace std;
typedef vector<int> vI;
typedef vector<int>::iterator vIter;

void printArray(vector<int> A) {
    for (vector<int>::iterator iter=A.begin(); iter != A.end(); ) {
        cout << *iter;
        iter++;
        if (iter != A.end()) 
            cout << ", ";
        else 
            cout << "\n";
    }
}

void generateRandomArray(vector<int> &A, int n) {
    A.clear();
    for (int i=0; i < n; i++) {
        A.push_back(rand()%1024);
    }
}

void swap(vector<int> &A, int i, int j) {
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

void quickSort(vector<int> &A, int lo, int hi) {
    if (hi < lo) return;
    
    int pivot = lo, swapIndex = lo+1;
    for (int i=lo+1; i <= hi; i++) {
        if (A[i] < A[pivot]) {
            swap(A, i, swapIndex);
            swapIndex++;
        }
    }
    swap(A, pivot, swapIndex-1);
    quickSort(A, lo, swapIndex - 2);
    quickSort(A, swapIndex, hi);
}

void qSort(vector<int> &A) {
    quickSort(A, 0, (A.size()-1));
}

vector<int> mergeSortedArrays(vector<int> A, vector<int> B) {
    vI sorted;
    vIter one, two;
    for (one = A.begin(), two = B.begin(); one != A.end() && two != B.end(); ){
        if (*one < *two) {
            sorted.push_back(*one);
            one++;
        } else {
            sorted.push_back(*two);
            two++;
        }
    }
    while(one != A.end()) {
        sorted.push_back(*one);
        one++;
    }
    while(two != B.end()) {
        sorted.push_back(*two);
        two++;
    }
    return sorted;
}

vector<int> mergeSort(vector<int> A, int low, int high) {
    if (high <= low) {
        vector<int> retArray;
        if (low == high) { 
            retArray.push_back(A[low]);
        } 
        return retArray; 
    }
    
    int mid = (high + low)/2 + 1;
    
    vector<int> one = mergeSort(A, low, mid-1);
    vector<int> two = mergeSort(A, mid, high);
    vector<int> sorted = mergeSortedArrays(one, two);
    return sorted;
}