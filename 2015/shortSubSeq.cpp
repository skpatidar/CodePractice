#include<iostream>
#include<vector>
#include<stdlib.h>
#include<iomanip>
#include<deque>
#include<math.h>
#include<map>

using namespace std;

bool updateSubString(string &A, int &start, int &end, const int &current, int &length, const map<char, bool> foundHash) {
    int newStart = start;
    char endChar = A[current];
    char currChar = A[newStart];
    cout << "\tUpdating : " << "start : " << start << ", end : " << end << ", current : " << current << ", length : " << length << "\n";
    while( (A[newStart] == endChar || !foundHash.count(currChar) ) && (newStart <= end)) {
        newStart++;
        currChar = A[newStart];
        cout << "\t\t newStart : " << newStart << "\n";
    }
    
    int newLength = (current-newStart+1);
    cout << "\tUpdate attempt : newStart : " << newStart << " newLength : " << newLength << "\n";
    if( newLength < length ){
        start = newStart;
        end = current;
        length = newLength;
        return true;
    }
    return false;
}

int main() {
    string str, charlist; 
    cout << "Enter string : ";
    cin >> str;
    
    cout << "Enter char list : ";
    cin >> charlist;
    
    cout << "Looking for shortest sub-string in string " << str << " containing charlist " << charlist << "\n";
    
    // Hash Map of required chars 
    map<char,bool> requiredHash;
    map<char,bool> foundHash;
    char currChar;
    
    for(int i=0; i < charlist.size(); i++) {
        currChar = charlist[i];
        requiredHash[currChar] = true;
    }
    
    int start = -1, end = -1;
    int current = 0, length = 0;
    int charsFound = 0;
    while (current < str.size()) {
        cout << "Start : " << start << ", end : " << end << ", current : " << current << ", length : " << length << "\n";
        currChar = str[current]; 
        if(requiredHash[currChar]) {
            if (foundHash[currChar] == 0) {
                if(start == -1) {
                    start = current;   
                    end = current; 
                } else {
                    end = current;
                }
                foundHash[currChar] = 1;
                length = end - start + 1;
                charsFound++;
            } else {
                cout << "Found a second occurance of char required : checking if length can be updated\n";
                bool updated = updateSubString(str, start, end, current, length, foundHash);
                if (updated) cout << "UPDATED : " << "Start : " << start << ", end : " << end << ", current : " << current << ", length : " << length << "\n";
                else cout << "NOT-UPDATED : " << "Start : " << start << ", end : " << end << ", current : " << current << ", length : " << length << "\n";
            }
        }
        current++;
    }
    
    if (charlist.size() == charsFound) {
        cout << "Shortest Substring : " << str.substr(start, length) << "\n";
    } else {
        cout << "NO MATCH !\n";
    }
    
    return 0;
}
    