#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

typedef vector<int> 		vInt;
typedef vector<int>::iterator 	vIntIter;

#define MAX_LINE_LENGTH 4

unsigned int setBits ( unsigned int byte, int startBit, int endBit) {
	unsigned int allOnes = (unsigned int) (pow(2,32) - 1);
	allOnes = allOnes >> (startBit-1); 
	allOnes = allOnes << (startBit-1);

	allOnes = allOnes << (32 - endBit);
	allOnes = allOnes >> (32 - endBit);

	return (unsigned int) (allOnes | byte);
}

int main (int argc, char *argv[]) {
	if (argc < 3) { 
		cout << "Provide x1 and x2 in b/w {0, 128} on commandline \nExiting\n"; exit(0); 
	} 
	int x1 = atoi(argv[1]);
	int x2 = atoi(argv[2]);
	cout << "Draw a line b/w " << x1 << " and " << x2 << "\n"; 
	
	unsigned int lineData[MAX_LINE_LENGTH];
	for (int i = 0; i < MAX_LINE_LENGTH; i++ ) lineData[i] = 0;

	int startByte = x1 / 32;	
	int startBit = x1 % 32 + 1;	
	int endByte = x2 / 32;	
	int endBit = x2 % 32 + 1;

	// Update Buffer
	if (endByte != startByte) { 
		lineData[startByte] = setBits(lineData[startByte], startBit, 32);
		lineData[endByte] = setBits(lineData[endByte], 1, endBit);
	} else {
		lineData[startByte] = setBits(lineData[startByte], startBit, endBit);
	}
	for (int i = startByte+1; i < endByte; i++) lineData[i] |= (unsigned int) (pow(2,32) - 1);

	//Draw Line Data
	for (int i = 0; i < MAX_LINE_LENGTH; i++ ) {
		unsigned int fourByte = lineData[i];
		while(fourByte) {
			if (fourByte & 1) cout << "-";
			else cout << ".";
			fourByte = fourByte >> 1;
		}
		cout << "\n";
	}
	cout << "\n";	
}
