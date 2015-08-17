#include <iostream>
#include <string.h>
#include <math.h>

using namespace std;

string getGreyCode( int n, int k ) {
	if ( !k || !n ){ return ""; }
	string out = "";
	if ( n > pow(2,k-1) ) {
		out = "1";
		out += getGreyCode(pow(2,k)-n+1, k-1);
	} else {
		out = "0";
		out += getGreyCode(n, k-1);
	}
	return out;	
}
int main(int argc, char *argv[]) {
	if ( argc < 3 ) { 
		cout << "Usage: ./a.out n k\nExiting .... \n";
		return 1;
	}
	int n = atoi(argv[1]);
	int k = atoi(argv[2]);
	if ( n > pow(2,k) ) {
		cout << "Invalid 'n' for given 'k'\nExiting ....\n";
		return 1;
	}
	string s;
	s = getGreyCode(n, k);
	cout << "Element " << n << "th " << "in " << k << " bit grey code is " << s << "\n";
	return 0;
}
