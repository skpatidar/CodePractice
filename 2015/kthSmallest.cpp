#include "utility.h"

int getKthSmallest(vector<int>& A, int low, int high, int k) {
    if (low == high) {
        if (low != k) {
            cout << "ERROR : 1 element array and k != low\n";
            exit(1);
        }
        return A[low];
    }
    cout << "Low = " << low << " high = " << high << " k = " << k << "\n";
    int pivot = low, swapWith = pivot + 1;
    for (int i=low+1; i <= high; i++) {
        if (A[i] < A[pivot]) {
            swap(A, pivot, i);
            swap(A, swapWith, i);
            pivot = swapWith;
            swapWith = pivot + 1;
            printArray(A);
        }
    }
    cout << "Ended with pivot = " << pivot << " low = " << low << " high = " << high << "\n";
    if (pivot == k ) {
        return A[k];
    } else if ( pivot > k ) {
        cout << "Calling with low = " << low << " high = " << pivot - 1 << " k = " << k << "\n";
        printArray(A);
        return getKthSmallest(A, low, pivot - 1, k);
    } else { 
        cout << "Calling with low = " << pivot+1 << " high = " << high << " k = " << k << "\n";
        printArray(A);
        return getKthSmallest(A, (pivot+1), high, k);
    }
}

int main(int argc, char *argv[]) { 
    //srand(time(NULL));
    vector<int> A; 
    int n = atoi(argv[1]); 
    int k = atoi(argv[2]);

    cout << "Initial array for size " << n << " : "; generateRandomArray(A, n); printArray(A);
    cout << "K = " << k << " th smallest element = " << getKthSmallest(A, 0, A.size()-1, k-1) << "\n";
    
    qSort(A);
    printArray(A);
    return 0;
}