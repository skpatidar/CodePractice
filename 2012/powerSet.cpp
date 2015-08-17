#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

typedef vector<int> 		vInt;
typedef vector<int>::iterator 	vIntIter;

void powerSet(string s) {
	if (!s.size()) return;

	int len = s.size();
	for ( int i=0; i < pow(double(2.0), double(len)); i++ ) {
		int tempLen = len;
		int pattern = i;
		cout << "{ ";
		while(tempLen) {
			if ( pattern & 1 ) {
				cout << s[tempLen-1] << ",";
			}
			tempLen--;
			pattern = pattern >> 1;
		}
		cout << "}\n";
	}
}

int main (int argc, char *argv[]) {
	if (argc < 2) { 
		cout << "Provide nElements on commandline \nExiting\n"; exit(0); 
	} 
	srand(time(NULL));

	string set(argv[1]);

	cout << "Power Set for Set : " << set << "\n"; 
	powerSet(set);	
}
