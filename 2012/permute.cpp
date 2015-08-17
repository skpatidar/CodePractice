#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <set>

using namespace std;

void createPermutations(string curPermute, set<char> s) {
	if (s.empty()) {
		cout << "Permutation : " << curPermute << "\n";
		return;
	}
	for ( set<char>::iterator it = s.begin(); it != s.end(); ++it ) {
		string newPermute = curPermute + *it;
		set<char> newSet = s;
		newSet.erase(*it);
		createPermutations(newPermute, newSet);
	}
}

void permute(string s) { 
	set<char> charSet;
	for (int i=0; i < s.length(); i++) {
		charSet.insert(s[i]);
	}
	string init;
	createPermutations(init, charSet);
}

int main (int argc, char *argv[]) {
	if (argc < 2) { 
		cout << "Provide string on commandline \nExiting\n"; exit(0); 
	} 
	string s(argv[1]);

	permute(s);	
	
	return 0;
}
