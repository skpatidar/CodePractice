#include <iostream>
#include <vector>
#include <iterator>
#include <stdlib.h>

using namespace std;

typedef	vector<int>		vInt;
typedef	vector<int>::iterator	viIter;
typedef	ostream_iterator<int>	output;

int randMod1K() { return rand()%1024;}
viIter quickSelect( viIter from, viIter to) {
	viIter front = from;
	viIter back = to - 1;
	int pivot = *front;
	front++;
	while (front < back) {
		while ( front < back && pivot > *front){ front++;}	
		while ( front < back && pivot <= *back){ back--;}
		swap(*front, *back);	
	}
	if (pivot >= *front) { swap(*from, *front); return front;}
	else { swap(*from, *(front-1)); return front-1;}
}
void quickSort( viIter from, viIter to ) {
	if ( from < (to-1) ) {
		viIter pivot = quickSelect (from, to);
		quickSort(from, pivot);
		quickSort(pivot+1, to);
	}
}
int main (int argc, char *argv[]) {
	int n = atoi(argv[1]);
	vInt	v(n);
	viIter vBegin = v.begin();	
	viIter vEnd = v.end();	

	srand(time(NULL));
	generate(vBegin, vEnd, randMod1K);

	cout << "Array before sorting : \n";
	copy(vBegin, vEnd, output(cout,"\t"));
	quickSort(vBegin, vEnd);
	cout << "\nArray after sorting : \n";
	copy(v.begin(), v.end(), output(cout,"\t"));
	cout << "\n";
	return 0;	
}
