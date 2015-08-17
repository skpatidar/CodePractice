#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

typedef vector<int> 		vInt;
typedef vector<int>::iterator 	vIntIter;

void incSubSeq(vector<int>& v) {
	vector<int> subSeqAt(v.size());
	vector<int> parentId(v.size());

	for (int i=0; i < v.size(); i++) {
		parentId[i] = i;

		int maxSeqSize = 1;
		int j = i - 1;
		while (j >=0) {
			if (v[j] < v[i] && subSeqAt[j] + 1 > maxSeqSize) {
				maxSeqSize = subSeqAt[j] + 1;
				parentId[i] = j;
			}
			j--;
		}
		subSeqAt[i] = maxSeqSize;
	}

	int longestEnd = 0;
	for ( int i=0; i < subSeqAt.size(); i++ ) {
		if (subSeqAt[i] > subSeqAt[longestEnd]) {
			longestEnd = i;
		}
	}
	
	cout << "Longest Increasing Sub Seq : "; 
	int i = longestEnd;
	while ( parentId[i] != i ) {
		cout << v[parentId[i]] << " > ";
		i = parentId[i];
	}
	cout << "X\nSeq Length : " << subSeqAt[longestEnd] << "\n";
}

int randMod100() { return rand()%100; }

int main (int argc, char *argv[]) {
	srand(time(NULL));

	vInt v(20);
	generate(v.begin(), v.end(), randMod100);

	cout << "Sequence : ";
	for (vIntIter iter = v.begin(); iter != v.end(); iter++) {
		cout << *iter << " ";
	}
	cout << "\n";

	incSubSeq(v);	

	return 0;
}
