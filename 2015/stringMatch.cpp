// String match with input string containing * and ? 
// http://www.geeksforgeeks.org/wildcard-character-matching/

#include "utility.h"
#include <stack>

bool isMatch(string S, string input) {
    string::iterator sIter = S.begin();
    string::iterator inIter = input.begin();
    
    while(inIter != input.end() && sIter != S.end()) {
        if (*inIter=='?') {
            inIter++;
            sIter++;
        } else if (*inIter=='*') {
            while(*inIter == '*' || *inIter == '?') 
                inIter++;
            while(*sIter != *inIter && sIter != S.end())
                sIter++;
        } else if (*inIter != *sIter) {
            return false;
        } else {
            inIter++;
            sIter++;
        }
    }
    
    if (inIter != input.end())
        return false;
    else 
        return true;
}

string reverseString(string in) {
    string::iterator sIter = in.end() - 1;
    string out; 
    while(sIter != in.begin()) {
        out += *sIter;
        sIter--;
    }
    out += *sIter;
    
    return out; 
}

string reverseWords(string in) {
    // Reverse order of words in a sentence
    stack<string> revStringStack;
    string curWord; 
    
    string::iterator sIter = in.begin();
    while(sIter != in.end()) {
        curWord = "";
        while(*sIter != ' ' and sIter != in.end()) {
            curWord += *sIter;
            sIter++;    
        }
        revStringStack.push(curWord);
        while(*sIter == ' ' and sIter != in.end()) {
            sIter++;
        }
    }
    
    string out; 
    while(!revStringStack.empty()) { 
        out += revStringStack.top();
        out += ' ';
        revStringStack.pop();
    }
    
    return out;
}

string reverseWordsInPlace(string in) {
    stack<char> curWord; 
    string::iterator sIter = in.begin();
    string out; 
    while(sIter != in.end()) {
        while(*sIter != ' ' and sIter != in.end()) {
            curWord.push(*sIter);
            sIter++;    
        }
        while(!curWord.empty()) {
            out += curWord.top();
            curWord.pop();
        }
        out += ' ';
        while(*sIter == ' ' and sIter != in.end()) {
            sIter++;
        }
    }
    return out;
}

int main() {

    cout << "\nisMatch:strange, str : " << isMatch("strange", "str");
    cout << "\nisMatch:strange, s*n : " << isMatch("strange", "s*r");
    cout << "\nisMatch:strange, st?a : " << isMatch("strange", "st?a");
    cout << "\nisMatch:strange, stn : " << isMatch("strange", "stn");
    cout << "\nisMatch:strange, s*k : " << isMatch("strange", "s*k");
    cout << "\nisMatch:strange, str?g : " << isMatch("strange", "str?g");
    
    string in("Cat jumped over a box");
    cout << "\nOriginal string : " << in; 
    cout << "\nReversed string : " << reverseString(in);
    cout << "\nReverse words : " << reverseWords(in);
    cout << "\nReverse individual words : " << reverseWordsInPlace(in);
    
    return 0;
}