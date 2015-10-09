// http://readyforsoftwareinterview.blogspot.in/2015/02/calculate-sum-of-nested-list-of-int.html?view=sidebar
// http://readyforsoftwareinterview.blogspot.in/2015/02/implement-queue-fifo-using-2-stacks.html?view=sidebar
// http://readyforsoftwareinterview.blogspot.in/2013/04/find-words-in-matrix-of-latters.html?view=sidebar
// http://readyforsoftwareinterview.blogspot.in/2013/04/design-cache-with-auto-deletion.html?view=sidebar

#include "utility.h"
#include <stack>
#define SIZE 8
typedef vector<vector<char > >::iterator vvcIter;
typedef vector<char>::iterator vcIter;

int calcNestedVal(string s) {
    string::iterator sIter = s.begin();
    int val = 0;
    int openCount = 0;
    
    while(sIter != s.end()) {
        if (*sIter == '{') openCount++;
        else if (*sIter == '}') openCount--;
        else if (*sIter == ',') ;
        else if (*sIter >= '0' && *sIter <= '9') {
            int cur = *sIter - '0';
            val += openCount * cur;
        } else {
            cout << "Unknown character : " << *sIter << " in string : " << s << "\n";
            exit(1);
        }
        if (openCount < 0) {
            cout << "Invalid pair of brackets in string : " << s << "\n";
            exit(1);
        }
        sIter++;
    }
    if (openCount) {
        cout << "Invalid pair of brackets in string : " << s << "\n";
        exit(1);
    }
    return val;
}

class Queue {
    stack<int> inbox;
    stack<int> outbox;
    int sz;
    
    public:
    Queue();
    int pop();
    int push(int);
    bool isFull();
    bool isEmpty();
    int size();
};

Queue::Queue() {
    sz = 0;
}

int Queue::push(int d) {
    if (isFull()) return -1;
    inbox.push(d);
    sz++;
    return d;
}

int Queue::pop() {
    if(isEmpty()) return -1;
    while(!inbox.empty()) {
        outbox.push(inbox.top());
        inbox.pop();
    }
    
    int val = outbox.top();
    outbox.pop();
    
    while(!outbox.empty()) {
        inbox.push(outbox.top());
        outbox.pop();
    }
    sz--;
    return val;
}

bool Queue::isFull() {
    return (inbox.size() > SIZE); 
}

bool Queue::isEmpty() {
    return inbox.empty();
}

int Queue::size() {
    return sz;
}

int findWordAt(vector<vector< char > > A, int y, int x, string s) {
    int ySize = A.size();
    int xSize = A[0].size();

    cout << "Looking for " << s << " starting at [" << y << "," << x << "] in horizontal direction\n";
    string::iterator sIter = s.begin();
    
    int wordCount = 0;

    // Horizontal 
    int tempx = x;
    while(sIter != s.end() && tempx <= xSize) {
        if (*sIter == A[y][tempx]) {
            tempx++;
            sIter++;
        } else { 
            break;
        }
    }
    if (sIter == s.end()) { 
        cout << "Found a match for word = " << s << " in horizontal direction starting at [" << y << "," << x << "]\n";
        wordCount++;
    }
    
    // Vertical 
    int tempy = y;
    sIter = s.begin();
    while(sIter != s.end() && tempy <= ySize) {
        if (*sIter == A[tempy][x]) {
            tempy++;
            sIter++;
        } else { 
            break;
        }
    }
    if (sIter == s.end()) { 
        cout << "Found a match for word = " << s << " in vertical direction starting at [" << y << "," << x << "]\n";
        wordCount++;
    }
    
    // Diagonal
    tempy = y;
    tempx = x;
    sIter = s.begin();
    while(sIter != s.end() && tempy <= ySize && tempx <= xSize) {
        if (*sIter == A[tempy][tempx]) {
            tempy++;
            tempx++;
            sIter++;
        } else { 
            break;
        }
    }
    if (sIter == s.end()) { 
        cout << "Found a match for word = " << s << " in diagonal direction starting at [" << y << "," << x << "]\n";
        wordCount++;
    }
    
    return wordCount;
}

int isWordExists(vector<vector< char > > A, string s) {
    vector<pair<int, int > > pivots;
    vvcIter yIter = A.begin();
    vcIter xIter = (*yIter).begin();
    while(yIter != A.end()) {
        xIter = (*yIter).begin(); 
        cout << "\n[";
        while(xIter != (*yIter).end()) {
            if (*xIter == s[0]) {
                pivots.push_back(make_pair((yIter - A.begin()), xIter - (*yIter).begin()));
            }
            cout << *xIter << ",";
            xIter++;
        }
        cout << "]\n";
        yIter++;
    }
    
    // Print pivots 
    vector<pair<int, int > >::iterator pIter; 
    pIter = pivots.begin();
    
    cout << "Found " << pivots.size() << " pivots\n";
    int wordCount = 0;
    while(pIter != pivots.end()) {
        cout << "\n\t[" << (*pIter).first << ", " << (*pIter).second << "]";
        wordCount += findWordAt(A, (*pIter).first, (*pIter).second, s);
        pIter++;
    }
    
    return wordCount;
}

int main() {
    
    {
    string s = "{1,2,{3,{4}}}";
    cout << "String = " << s << " Val = " << calcNestedVal(s);
    }
    
    {
    Queue q;
    
    cout << "\nPop : " << q.pop(); 
    cout << "\nIs Empty : " << q.isEmpty();
    cout << "\nPush 1 : " << q.push(1);
    cout << "\nIs Empty : " << q.isEmpty();
    cout << "\nSize : " << q.size();
    cout << "\nPush 2 : " << q.push(2);
    cout << "\nPush 3 : " << q.push(3);
    cout << "\nPush 4 : " << q.push(4);
    cout << "\nPop : " << q.pop();
    cout << "\nPop : " << q.pop();
    cout << "\nSize : " << q.size();
    cout << "\nPop : " << q.pop();
    cout << "\nPop : " << q.pop();
   }
    
    {
    vector<vector<char > > A; 
    
    vector<char> v;
    v.push_back('f');v.push_back('x');v.push_back('o');v.push_back('s');v.push_back('f');v.push_back('u');
    A.push_back(v);
    v.clear();
    v.push_back('g');v.push_back('b');v.push_back('m');v.push_back('r');v.push_back('a');v.push_back('r');
    A.push_back(v);
    v.clear();
    v.push_back('k');v.push_back('a');v.push_back('a');v.push_back('x');v.push_back('t');v.push_back('v');
    A.push_back(v);
    v.clear();
    v.push_back('i');v.push_back('s');v.push_back('l');v.push_back('l');v.push_back('x');v.push_back('f');
    A.push_back(v);
    v.clear();
    v.push_back('t');v.push_back('s');v.push_back('l');v.push_back('l');v.push_back('l');v.push_back('x');
    A.push_back(v);
    v.clear();
    v.push_back('o');v.push_back('x');v.push_back('x');v.push_back('x');v.push_back('x');v.push_back('o');
    //A.push_back(v);
    v.clear();
    
    string s = "all";
    cout << "Is Word " << s << " Exists in A : " << isWordExists(A, s);
    }
    
    return 0;
}