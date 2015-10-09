#include "utility.h"
#include <set>

int findLongestContiSeq(vector<int> A) {
    set<int> S;
    for (vIter iter = A.begin(); iter != A.end(); iter++) {
        S.insert(*iter);
    }
    int max = 1; 
    for (vIter iter = A.begin(); iter != A.end(); iter++) {
        int val = *iter;
        if (S.find(val - 1) == S.end()) {
            int len = 1;
            while(S.find(val+len) != S.end()) {
                len++;
            }
            if (len > max) max = len;
        }
    }
    return max;
}

int main() {
    static const int arr[] = {1, 9, 3, 10, 4, 20, 2, 8, 7, 6, 0, 11};
    vector<int> A (arr, arr+sizeof(arr)/sizeof(arr[0]));
    
    cout << "Longest seq with contiguous numbers is of size = " << findLongestContiSeq(A);
    
    return 0;
}