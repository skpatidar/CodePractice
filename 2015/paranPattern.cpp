#include<iostream>
#include<vector>
#include<stdlib.h>
#include<string> 

using namespace std;

int validParan (string s, int n, int open, int close) {
    if ( (open + close) == n ) {
        if (open==close) {
            cout << s << "\n";
            return 1;
        }
        return 0;
    }
    
    int openCount = 0, closeCount = 0;
    
    if (open < n/2) {
        string str = s + '('; 
        openCount = validParan(str, n, open+1, close);
    } 
    
    if (close < open) {
        string str = s + ')';
        closeCount = validParan(str, n, open, close+1);
    }
    
    return openCount + closeCount;
}

int main() {
    int n;
    cout << "Enter length n :";
    cin >> n;
    
    if (n < 1 || n % 2) {
        cout << "No patterns possible\n"; 
        return 0;
    }
    
    string s;
    cout << "Number of patterns possible : " << validParan(s, n, 0, 0);
}