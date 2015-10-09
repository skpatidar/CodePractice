#include "utility.h"
#include <unordered_map>

int getUnique(vector<int> A) {
    unordered_map<string, int> hashMap;
    for (vector<int>::iterator it = A.begin(); it != A.end(); it++) {
        if (hashMap.count(*it)) {
            hashMap[*it] = 1 - hashMap[*it] 
        } else { 
            hashMap.insert(std::make_pair<string, int>(to_string(*it), 1));
        }
    }
    string value;
    unordered_map<string, int>::iterator iter;
    for (iter = hashMap.begin(); iter != hashMap.end(); iter++) {
        cout << "[" << *iter->first << "] => " << *iter->second << "\n";
        if (*iter->second) { 
            value = *iter->first;
        }
    }
    return value;
}

int main() {
    vector<int> A;
    A.push_back(11);
    A.push_back(11);
    A.push_back(13);
    A.push_back(13);
    A.push_back(15);
    A.push_back(15);
    A.push_back(14);
    A.push_back(14);
    A.push_back(12);
    
    cout << "Unique number in array is : " << getUnique(A) << "\n"; 
    
    return 0;
}