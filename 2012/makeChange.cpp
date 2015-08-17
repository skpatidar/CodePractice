#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

int makeChange(vector<int>& k, int N) {
	int *M, *C;
	M = new int [N];
	C = new int [N];
	M[0] = 0;
	C[0] = -1;
	for (int n=1; n <= N; n++) {
		int bCase = INT_MAX;
		for ( int i=0; i < k.size(); i++ ) {
			if ( n - k[i] >= 0 ) {
				if (bCase > M[n-k[i]] + 1) {
					bCase = M[n-k[i]] + 1;
					C[n] = k[i];
				}
			}
		}
		M[n] = bCase;
	}
	cout << "Coins required to make change for N = " << N << " : ";
	int i = N;
	while (C[i]>0) {
		cout << C[i] << " ";
		i = i - C[i];
	} cout << "\n";
	return M[N];
}

int main (int argc, char *argv[]) {
	vector<int> k;
	cout << "Coins : ";
	k.push_back(1);
	k.push_back(3);
	k.push_back(5);
	k.push_back(7);
	k.push_back(10);
	int N = 29;

	cout << "Change for N = " << N << " will take M = " << makeChange(k, N) << " coins\n"; 
	return 0;
}
