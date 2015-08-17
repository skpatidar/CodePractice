#include<iostream>
#include<vector>
#include<stdlib.h>
#include<math.h>
#include<string>
#include<algorithm>
#include<iterator>

using namespace std;

int sum(vector<int>& V, int from, int to) {
	int total = 0;
	for ( int i=from; i <= to; i++ ) {
		total += V[i];
	}
	return total;
}

int partition(vector<int>& V, int n, int k) {
	// Base Case - If one painter remains
	if ( k==1 ) { 
		return sum(V, 0, n-1);
	} 
	// Base Case - If one board remains 
	if ( n==1 ) {
		return V[0];
	}
	// Minimum of the - Maximum of the subpartitions 
	int best = INT_MAX;
	for ( int j = 2; j <= n; j++ ) {
		best = min (best, max(partition(V, j, k-1), sum(V, j, n-1)));	
	}
	return best;
}

int partitionDP(vector<int>& V, int n, int k) {
	// Cumulative Score for j to n-1 cases 
	int cum[100] = {0};
	for (int i = 1; i <= n; i++)
		cum[i] = cum[i-1] + V[i-1];

	int M[100][100];
	for (int i = 1; i <= k; i++) {
		M[1][i] = V[0];
	}
	for (int i = 1; i <= n; i++) {
		M[i][1] = cum[i];
	}

	for (int painters = 2; painters <= k; painters++) {
		for (int boards = 2; boards <= n; boards++) {
			int best = INT_MAX;
			for ( int part = 1; part <= boards; part++ ) {
				best = min( best,
						max( M[part][painters-1], cum[boards] - cum[part])
					  );
			}
			M[boards][painters] = best;
		}
	}
	
	for (int boards = 0; boards < n; boards++) {
		for (int painters = 0; painters < k; painters++) {
			cout << M[boards][painters] << " ";
		}
		cout << "\n";
	}
	return M[n][k];
}

int main(int argc, char *argv[]) {
	srand(time(NULL));
	vector<int> V; 
	for (int i = 0; i < 5; i++ ) {
		V.push_back(rand()%15+1);
	}
	int k = 3;
	int best = partitionDP(V, V.size(), k);
	cout << "Max Work on Vector V = : ";
	for (int i = 0; i < 5; i++ ) { cout << V[i] << " "; }
	cout << "\nis : " << best << "\n";

	return 0;
}
