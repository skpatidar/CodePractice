#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef vector<int> 		vInt;
typedef vector<int>::iterator 	vIntIter;

int createPattern(string s, int nElem, int openCount) {
	int leftCount = 0, rightCount = 0;
	if (!nElem) {
		if (!openCount) {
			cout << s << "\n";
			return 1;
		}
		return 0;
	}
	if (openCount) { 
		leftCount = createPattern(s + ")", nElem-1, openCount-1);
	}
	if ( openCount < nElem ) {
		rightCount = createPattern(s + "(", nElem-1, openCount+1);
	}
	return leftCount + rightCount;
}

int main (int argc, char *argv[]) {
	if (argc < 2) { 
		cout << "Provide nElements on commandline \nExiting\n"; exit(0); 
	} 
	srand(time(NULL));

	int nElements = atoi(argv[1]);

	string pattern;
	cout << "Number of patterns possible : " << createPattern(pattern, nElements, 0) << "\n";	
}
