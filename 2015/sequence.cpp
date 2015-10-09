#include "utility.h"

int maxWaterTrap(vector<int> A) {
    int start = 0, end = 1, max = 0, size = A.size(), curWater=0;
    while(end < size) {
        curWater = 0;
        while(A[end] < A[start] && end < size) {
            curWater += (A[start] - A[end]);
            end++;
            //cout << "start = " << start << ", end = "  << end << ", curWater = " << curWater << "\n";
        }
        start = end;
        end = start + 1;
        if (max < curWater) max = curWater;
    }
    return max;
}

int maxAreaRect(vector<int> A) {
    int start = 0, end = 1, max = 0, size = A.size(), curArea=0;
    
    
    return max;
}

int main() {
    static const int arr[] = {3, 0, 0, 2, 0, 1, 4, 0, 0, 1, 5};
    //static const int arr[] = {3, 1, 1, 2, 4, 0, 4, 5};
    vector<int> A (arr, arr+sizeof(arr)/sizeof(arr[0]));
    
    cout << "Max water trapped is = " << maxWaterTrap(A);
    //cout << "Max area rectangle = " << maxAreaRect(A);
    return 0;
}