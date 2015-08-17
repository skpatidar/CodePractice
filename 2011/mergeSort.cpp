//Merge Sort 
#include <iostream>
#include <vector>
#include <iterator>
#include <stdlib.h>

using namespace std;

typedef	vector<int>		vInt;
typedef vector<int>::iterator	viIter;
typedef ostream_iterator<int>	copyOut;

// Random number generator b/w 0 and 1024
int randMod1K() { return rand()%1024; }

// Merge Function
vInt merge( vInt left, vInt right) {
	vInt out;
	viIter	iterLeft = left.begin();
	viIter	iterRight = right.begin();
	while (iterLeft != left.end() && iterRight != right.end()) {
		if (*iterLeft <= *iterRight){out.push_back(*iterLeft);iterLeft++;}
		else {out.push_back(*iterRight); iterRight++;}
	}
	while (iterLeft != left.end()) {
		out.push_back(*iterLeft);
		iterLeft++;
	}
	while (iterRight != right.end()) {
		out.push_back(*iterRight);
		iterRight++;
	}
	return out;
}

// Merge Sort Function
vInt mergeSort ( viIter begin, viIter end ) {
	if ( begin + 1 == end ) { return vector<int>(begin, end); }

	viIter	middle = begin + (end - begin)/2;

	vInt left = mergeSort(begin,middle);
	vInt right = mergeSort(middle,end);

	vInt out = merge(left, right);

	return out;
}

int main (int argc, char *argv[]) {
	if ( argc < 2 ) {
		cout << "Enter number of elements for sorting\nExiting ...\n";
		return 1;
	}
	int n = atoi(argv[1]);
	cout << "Number of elements for sorting : " << n << "\n";

	vInt	inputArr(n);
	viIter	aBegin = inputArr.begin();
	viIter	aEnd = inputArr.end();
	generate(aBegin, aEnd, randMod1K);

	cout << "Array to be sorted : \n";
	copy (aBegin, aEnd, copyOut(cout,"\t"));
	cout << "\n";
	
	vInt	vOut = mergeSort(aBegin, aEnd);

	cout << "Array sorted : \n";
	copy (vOut.begin(), vOut.end(), copyOut(cout,"\t"));
	cout << "\n";

	return 0;
}
