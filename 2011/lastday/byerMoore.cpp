#include <iostream>
#include <vector>
#include <time.h>
#include <iterator>
#include <string.h>
using namespace std;

vector<int> generateTable1(string a) {
	int size = a.size();
	cout << "Size of string : " << size << "\n";
	vector<int> table(size);

	for ( int i=1; i <= size; i++ ){
		string match = a.substr(size-i,i);
		cout << "\nMatching : " << match << " : with";
		for ( int k=1, j=size-1; j >= i; j--,k++ ) {
			string matchingWith = a.substr(j-i,i);
			cout << "\n\t" <<  matchingWith;
			if( match[0] != matchingWith[0] && match.substr(1,match.size()) == matchingWith.substr(1,match.size()) ) {
				cout << "\t\tCount is " << k << "\n"; 
				break;
			}
		}
		cout << "\t\tCount is " << size <<"\n";
	}
	return table;
}

int main() {
	string a("ANPANMAN");
	vector<int> table1;
	table1 = generateTable1(a);

	return 0;
}


