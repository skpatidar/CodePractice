#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

void primeSeive(int n, bool primes[]) {
	primes[0] = primes[1] = 0;
	for (int i=2; i <=n ; i++) {
		primes[i] = 1;
	}

	int i = 2;
	while ( i < sqrt(n) ) {
		for ( int j = i * i; j <= n; j += i ) {
			primes[j] = 0;
		}
		i++;
		while (i < sqrt(n) && primes[i] != 1) {
			i++;
		}
	}

	for ( int i = 2; i <=n; i++) {
		if (primes[i]) {
			cout << i << " ";
		}
	}
	cout << "\n";
}

int main (int argc, char *argv[]) {
	int n = atoi(argv[1]);
	cout << "All primes for n = " <<  n << " are : ";
	bool *primes;
	primes = new bool[n];
	primeSeive(n, primes);

	return 0;
}
