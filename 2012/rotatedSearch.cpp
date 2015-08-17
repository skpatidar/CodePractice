#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

int binSearch(vector<int>& v, int search) {
	int left = 0, right = v.size() - 1;
	int middle;
	while (left <= right) {
		middle = left + (right - left)/2;
		cout << "Middle : " << middle << " Left : " << left << " Right : " << right << "\n";
		if (v[middle] == search) return middle; 
		else {
			if ( v[middle] >= v[left] ) {
				if (search >= v[left] && search < v[middle]) {
					right = middle - 1;
				} else {
					left = middle + 1;
				}
			} else { 
				if ( search > v[middle] && search <= v[right] ) {
					left = middle + 1;
				} else {
					right = middle - 1;
				}
			}
		}
	}
	return -1;
}
int main (int argc, char *argv[]) {
	srand(time(NULL));

	vector<int> v;
	for(int i=0; i < 17; i++) { 
		v.push_back(i);	
	}
	for(int i=0; i < v.size(); i++) { 
		cout << v[i] << " ";
	}
	cout << "\n";
	rotate(v.begin(), v.begin() + 9, v.end());
	for(int i=0; i < v.size(); i++) { 
		cout << v[i] << " ";
	}
	cout << "\n";

	int r = rand() % v.size();
	int search = v[r];
	cout << "Searchning for " << search << "\n";
	cout << "Found Element " << search << " at " << binSearch(v, search) << "\n";
	search = 16;
	cout << "Searchning for " << search << "\n";
	cout << "Found Element " << search << " at " << binSearch(v, search) << "\n";

	return 0;
}
