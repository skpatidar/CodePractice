#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

int maxArea(vector<int>& v) {
	int mArea = 0;
	int mBase = -1;
	for ( int i=0; i < v.size(); i++ ) {
		int l = i-1, r = i+1;
		while ( l >= 0 && v[l] >= v[i] ) l--;
		l++;
		while ( r < v.size() && v[r] >= v[i] ) r++;
		r--;
		int curArea = v[i] * ( (i - l) + (r - i) + 1);
		//cout << "L and R @ i " << l << " " << r << " " << i << "\n";
		if (mArea < curArea) {
			mArea = curArea;
			mBase = i;
		}
	}
	return mArea;
}

int main (int argc, char *argv[]) {
	vector<int> v;
	srand(time(NULL));
	cout << "Bar : ";
	for (int i=0; i < 5; i++) {
		v.push_back(rand()%8+1);
		cout << v[i] << " ";
	}
	cout << "\n";
	cout << "Max Area : " << maxArea(v) << "\n";
	return 0;
}
