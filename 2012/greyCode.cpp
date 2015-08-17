#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

typedef vector<int> 		vInt;
typedef vector<int>::iterator 	vIntIter;

string generateGreyCode(int n, int k) {
	if(!k) return "";
	int numCodes = pow((double)2.0, (double)k);
	if (n <= numCodes/2) { // Upper Half
		return ("0" + generateGreyCode(n, k-1) );
	} else { // Lower Half
		return ("1" + generateGreyCode( numCodes-n+1, k-1) );
	}
}

int main (int argc, char *argv[]) {
	if (argc < 3) { 
		cout << "Provide k (number of bits) and n (nth element)  \nExiting\n"; exit(0); 
	} 
	int k = atoi(argv[1]);
	int n = atoi(argv[2]);
	// Need nth elelment from a k-bit Gray Code

	cout << "Gray Code #" << n <<" for the " << k << "-bit : " << generateGreyCode(n, k) << "\n";	
}
