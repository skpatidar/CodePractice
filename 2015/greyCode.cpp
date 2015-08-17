#include<iostream>
#include<string>
#include<math.h>

using namespace std;

string getKthGreyCode(int nBits, int kPos) {
    int n = pow(2.0, float(nBits)), k = kPos;
    
    string s; 
    bool flipBit = 0;
    
    while (n > 1) {
        string outBit("0");
        bool upperHalf = 0;
        if (k > n/2) {
            upperHalf = 1;
        }
        
        if (upperHalf) {
            outBit = "1";
            k = k - n/2;
        }
        
        if (flipBit) {
            if (outBit=="0") outBit = "1";
            else outBit = "0";
        }
        
        if (upperHalf) flipBit = 1; 
        else flipBit = 0;
        
        s += outBit; 
        n /= 2;
    }
    return s;
}

int main() {
    int nBits, kPos;
    cout << "Input value for n bits : ";
    cin >> nBits;
    cout << "Input value for k (kth element) : ";
    cin >> kPos;
    
    string kthElement = getKthGreyCode(nBits, kPos);
    cout << "Kth element in " << nBits << " bit grey code is : " << kthElement;
    
    return 0;
}