#include<iostream>
#include<vector>
#include<stdlib.h>
#include<math.h>
#include<string>
#include<algorithm>
#include<iterator>

using namespace std;

void rotateArr1(vector<int>& v, int k) {
	reverse(v.begin(), v.end());
	reverse(v.begin(), v.begin()+k);
	reverse(v.begin()+k, v.end());
}

int main(int argc, char *argv[]) {
	vector<int> arr;
	int k = 4;
	for (int i=1; i<=10; i++) { arr.push_back(i); }
	rotateArr1(arr, k); 
	cout << "\nRotated by k : "; 
	copy(arr.begin(), arr.end(), ostream_iterator<int>(cout, " "));
	cout << "\n";
	return 0;
}
