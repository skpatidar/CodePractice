#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <set>

using namespace std;

vector<int> intersectSorted(vector<int>& v1, vector<int>& v2) { 
	vector<int> v;

	vector<int>::iterator iter1 = v1.begin(), iter2 = v2.begin();
	while ( iter1 != v1.end() && iter2 != v2.end() ) {
		if ( *iter1 > *iter2 ) 
			iter2++;
		else if ( *iter1 < *iter2 )
			iter1++;
		else {
			v.push_back(*iter1);
			iter1++;
			iter2++;
		}
	}
	return v;
}

int randMod() { return rand() % 20; }

int main (int argc, char *argv[]) {
	srand(time(NULL));

	vector<int> v1(7);
	vector<int> v2(9);

	generate(v1.begin(), v1.end(), randMod);
	generate(v2.begin(), v2.end(), randMod);

	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());
	
	cout << "V1 : ";
	for (int i=0; i < v1.size(); i++) {
		cout << v1[i] << " ";
	}
	cout << "\n";
	cout << "V2 : ";
	for (int i=0; i < v2.size(); i++) {
		cout << v2[i] << " ";
	}
	cout << "\n";

	cout << "Intersection : ";
	vector<int> v = intersectSorted(v1, v2);
	for (int i=0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
	cout << "\n";

	return 0;
}
