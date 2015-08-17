#include <iostream>
#include <vector>
#include <set>
#include <iterator>
#include <string.h>
#include <math.h>
using namespace std;

vector<set<char> > generatePowerSet(string inputSet) {
	vector<set<char> >	powerSet;

	int len = inputSet.size();
	for (int i=0; i < pow(2,len); i++ ) {
		set<char> cSet;
		int cnt = i;
		int counter = 0;
		while (cnt!=0) {
			if (cnt%2){ 
				cSet.insert(inputSet[counter]); 
			}
			cnt = cnt >> 1;
			counter++;
		}
		powerSet.push_back(cSet);
	}
	return powerSet;
}
int main (int argc, char *argv[]) {
	if ( argc < 2 ) { 
		cout << "Provide a string (to be used as a set) :./a.out <string>\nExiting ....\n"; 
		return 1; 
	}
	string inputSet(argv[1]);
	vector<set<char> >	powerSet;
	powerSet = generatePowerSet(inputSet);
	
	vector<set<char> >::iterator	s;
	set<char>::iterator c;
	for ( s = powerSet.begin(); s != powerSet.end(); s++ ) {
		cout << "Set : " << " : ";
		for ( c = (*s).begin(); c != (*s).end(); c++ ) {
			cout << *c << ", ";
		}
		cout << "\n";
	}
	return 0;
}	
