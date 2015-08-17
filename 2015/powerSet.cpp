#include<iostream>
#include<set>
#include<math.h>

using namespace std;

void printSet(set<char> S) {
    cout << "{";
    for (set<char>::iterator iter=S.begin(); iter != S.end();) {
        cout << *iter;
        iter++;
        if (iter != S.end())
            cout << ", ";
    }
    cout << "}\n";
}

void buildSet(string inputString, set<char>& S) {
    for (string::iterator iter = inputString.begin(); iter != inputString.end(); iter++ ){
        S.insert(*iter);
    }
}

int genPowerSet(set<char> S) {
    int size = S.size();
    long unsigned int twoPowN = (int) pow(2.0, float(size));
    set<char> currSet; 
    for (int i=0; i < twoPowN; i++) {
        set<char>::iterator currElement = S.begin();
        int currSetBitmap = i;
        currSet.clear();
        while (currSetBitmap != 0) {
            if (currSetBitmap & 1) {
                currSet.insert(*currElement);
            }
            currElement++;
            currSetBitmap >>= 1;
        }
        printSet(currSet);
    }
    return twoPowN;
}

int main() {
    cout << "Input a list of characters without spaces which can be used to build the set\n";
    string inputString;
    cin >> inputString; 
    cout << "You have input : " << inputString << "\n";
    
    set<char> S;
    buildSet(inputString, S);
    printSet(S);
    
    int numSets = genPowerSet(S);
    
    cout << "Printed " << numSets << " above\n";
    return 0;
}