
#include <iostream>
#include <vector>
#include <time.h>
#include <iterator>
using namespace std;

vector<int> longestIncSeq(vector<int> v) {
	vector<int> outV(v.size());
	for ( int i=0; i < v.size(); i++) {
		int max = 0;
		for ( int j=0; j < i; j++ )
			if ( v[i] > v[j] )
				if ( outV[j] > max )
					max = outV[j];
		outV[i] = max + 1;
	}
	return outV;
}	

int randMod1K() { return rand()%1024; }
int main () {
	srand(time(NULL));
	vector<int>	v(10);
	generate(v.begin(),v.end(),randMod1K);
	copy(v.begin(),v.end(),ostream_iterator<int>(cout," "));
	cout << "\n";
	vector<int> outV;
	outV = longestIncSeq(v);
	copy(outV.begin(),outV.end(),ostream_iterator<int>(cout," "));
	cout << "\n";
	return 0;
}
