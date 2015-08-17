#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>

using namespace std;

typedef	istream_iterator<int> istream_iterator_int;
typedef vector<int> vecI;

template<class ForwardIterator, class T>
int iota_n(ForwardIterator iter, int n, T value) {
	for (int i=0; i < n; i++) {
		*iter++ = value++;
	}
}

int main (int argc, char *argv[]) {
	int n = atoi(argv[1]);
	cout << "Number of elements : " << n <<"\n";

	vecI	v;
	//for ( int i=0; i < n; i++) {
	//	v.push_back(i);
	//}
	iota_n(v.begin(), n, back_inserter(v));
	random_shuffle(v.begin(), v.end());

	cout << "Random Seq : \n";
	copy(v.begin(), v.end(), ostream_iterator<int> (cout, "\n"));
	
	return 0;
}
