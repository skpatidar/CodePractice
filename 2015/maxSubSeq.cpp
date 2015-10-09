#include "utility.h"

int maxSumSubseq(vector<int> A, vector<int> &B, int end) {
    if (end == 0) {
        B[end] = A[end];
        return A[end];
    }
    int preSum = maxSumSubseq(A, B, end - 1); 
    if (preSum > 0) {
        B[end] = preSum + A[end];
    } else {
        B[end] = A[end];
    }
    return B[end];
}

int main() {
    vector<int> A;
    A.push_back(3);
    A.push_back(-4);
    A.push_back(-1);
    A.push_back(5);
    A.push_back(2);
    A.push_back(-4);
    A.push_back(9);
    A.push_back(1);
    A.push_back(-2);
    A.push_back(-1);
    A.push_back(2);
    
    vector<int> B; 
    B.resize(A.size());
    maxSumSubseq(A, B, A.size()-1);
    
    cout << "Array : \n";
    printArray(A);
    cout << "Sum Array : \n";
    printArray(B);
    
    return 0;
}