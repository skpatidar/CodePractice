#include "utility.h"

vector<string> perm(string s) {
    if (s.length() == 0) {
        vector<string> A;
        return A;
    }
    
    if (s.length() == 1) {
        vector<string> A;
        A.push_back(s);
        return A;
    }
    
    string pivot = s.substr(0, 1);
    string rest = s.substr(1, s.size()-1);
    vector<string> A = perm(rest);
    vector<string> B;
    string::iterator sIter;
    vector<string>::iterator vsIter;
    
    cout << "Pivot = " << pivot << " restString = " << rest << "\n";
    for (vsIter = A.begin(); vsIter != A.end(); vsIter++) {
        cout << ">>" << (*vsIter) << "\n";
        for (int i=0; i <= (*vsIter).length(); i++) {
            string temp = (*vsIter).substr(0, i) + pivot + (*vsIter).substr(i, (*vsIter).length() - i);
            cout << "\t" << temp << "\n";
            B.push_back(temp);
        }
    }
    return B;
}

int main() {
    string s = "asdf";
    vector<string> A = perm(s);
    cout << A.size() << " combinations of : " << s << "\n";
    for(vector<string>::iterator iter = A.begin(); iter != A.end(); iter++) {
        cout <<"\t" << *iter << "\n";
    }
    return 0;
}