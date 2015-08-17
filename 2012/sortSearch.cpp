#include <iostream>
#include <vector>
#include <math.h>
#include <iterator>

using namespace std;

typedef vector<int> 		vInt;
typedef vector<int>::iterator 	vIntIter;

int randMod1K() { return rand() % 128; }
void printVector(vector<int>& v) {
	for (vIntIter iter=v.begin(); iter != v.end(); iter++) {
		cout << *iter << " ";
	}
	cout << "\n";
}

vInt sortedMerge(vInt v1, vInt v2) {
	vector<int> sortedV;

	vIntIter iterV1 = v1.begin();
	vIntIter iterV2 = v2.begin();
	/*
	cout << "Merge 2 Vectors below \n";
	cout << "\tv1: "; printVector(v1);
	cout << "\tv2: "; printVector(v2);
	*/
	while (iterV1 != v1.end() && iterV2 != v2.end()) {
		if (*iterV1 < *iterV2) {
			sortedV.push_back(*iterV1);
			iterV1++;
		} else {
			sortedV.push_back(*iterV2);
			iterV2++;
		}
	}

	if(iterV1==v1.end()) {
		while (iterV2 != v2.end()) {
			sortedV.push_back(*iterV2);
			iterV2++;
		}
	} else {
		while (iterV1 != v1.end()) {
			sortedV.push_back(*iterV1);
			iterV1++;
		}
	}

	return sortedV;
}

vInt mergeSort(vInt v, int begin, int end) {
	if ( begin < end ) {
		int pivot = begin + ((end - begin + 1) / 2) - 1;		
		//cout << "Break at [" << begin << ", " << pivot << "], [" << pivot + 1 << ", " << end << "]\n";
		vector<int> v1 = mergeSort(v, begin, pivot);
		vector<int> v2 = mergeSort(v, pivot+1, end);
		vector<int> sortedV = sortedMerge(v1, v2);
		return sortedV;
	}

	vInt v1;
	v1.push_back(v[begin]);
	return v1;
}


int qPart(vector<int>& v, int begin, int end) {
	int storeIndex = begin;
	int pIndex = end;

	int iter = begin; 	
	while (iter < end) {
		if (v[iter] < v[pIndex]) {
			swap(v[iter], v[storeIndex]);
			storeIndex++;
		}
		iter++;
	}
	swap(v[pIndex], v[storeIndex]);

	return storeIndex;
}

int quickSort(vector<int>& v, int begin, int end) {
	if ( begin < end ) {
		int partition = qPart(v, begin, end); 
		int part1 = quickSort(v, 0, partition-1);
		int part2 = quickSort(v, partition+1, end); 
		return 1 + part1 + part2; 
	}
	return 0;
}

int binSearch(vInt& v, int& e, int begin, int end) {
	if ( begin <= end ) { 
		int pivot = begin + (end - begin + 1)/2; 
		if ( e == v[pivot] ) {
			return pivot;
		} 
		else if ( e < v[pivot] ) {
			return binSearch(v, e, begin, pivot-1); 
		} else {
			return binSearch(v, e, pivot+1, end); 
		}
	}
	return -1;
}

int main (int argc, char *argv[]) {
	if (argc < 2) { 
		cout << "Provide nElements on commandline \nExiting\n"; exit(0); 
	} 
	srand(time(NULL));

	int n = atoi(argv[1]);

	vInt v(n);
	generate(v.begin(), v.end(), randMod1K);
	cout << "\nUnSorted :\t"; printVector(v); 
	
	int randomSearch = v[0]; 

	int numPartitions = quickSort(v, 0, n-1);
	cout << "\nQuick Sorted (in " << numPartitions << " partitions) :\t";
	printVector(v);

	random_shuffle(v.begin(), v.end());
	vector<int> sortedV = mergeSort(v, 0, n-1);
	cout << "\nMerge Sorted :\t"; printVector(sortedV);
	
	int searchIndex = binSearch(sortedV, randomSearch, 0, n-1);
	cout << "Found element : " << randomSearch << " at Index " << searchIndex << "\n";

	randomSearch = rand() % 128;
	cout << "Found element : " << randomSearch << " at Index " << binSearch(sortedV, randomSearch, 0, n-1) << "\n";

	return 0;
}
