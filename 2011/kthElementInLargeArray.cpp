#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

typedef	vector<int>		vInt;
typedef vector<int>::iterator	viIter;
typedef ostream_iterator<int>	outputIterator;

int randMod1024() {
	return (rand() % 1024);
}

int main (int argc, char *argv[]) {
	if (argc < 3) {
		cout << "Usage : ./a.out totalElements k";
		exit(1);
	}

	int n = atoi(argv[1]);				//N Input Elements
	int k = atoi(argv[2]);				//Kth Shortest Element to be returned

	vInt	inputVector(n);
	viIter	iBegin = inputVector.begin();
	viIter	iEnd = inputVector.end();
	generate(iBegin, iEnd, randMod1024);		// Fill inuputVector with random numbers b/w 0 and 1024

	vInt	kElementVector(iBegin, iBegin + k - 1);	// Build a vector with first k Elements of inputVector
	viIter 	kBegin = kElementVector.begin();
	viIter	kEnd = kElementVector.end();
	make_heap(kBegin, kEnd);			// Build heap out of kElementVector
	
	//copy(kBegin,kEnd,ostream_iterator<int>(cout," "));
	//pop_heap(kBegin,kEnd);
	//cout << "\n" << *(kEnd-1) << "\n";
	//copy(kBegin,kEnd,ostream_iterator<int>(cout," "));
	//return 0;

	int heapMax = *kBegin;
	for (viIter fIter = iBegin + k; fIter != iEnd; fIter++ ) {	// Go over rest of elements from inputVector
		int iElement = *fIter;
		if ( iElement < heapMax ) {		// Only update the heap if incoming element from inputVector is smaller than heap MAX ELEMENT
			pop_heap(kBegin, kEnd);		// Pops and places the element at kEnd-1
			*(kEnd-1) = iElement;		// Replace it with new element : which will be inserted into heap below
			push_heap(kBegin, kEnd);	// Inserted
			heapMax = *kBegin;		
		}
	}

	sort_heap(kBegin, kEnd);
	cout << "Output :: \n\tKth largest element : " << *(kEnd-1) << "\n";

	sort(iBegin, iEnd);	
	cout << "Check :: \n\tKth largest element (from Sort output of Big Array) : " << *(iBegin+k-1) << "\n";

	return 0;	
} 
