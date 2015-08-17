#include<iostream>
#include<vector>
#include<stdlib.h>
#include<math.h>
#include<string>
#include<algorithm>
#include<iterator>

using namespace std;

int lDist(string s1, string s2) {
	if (!s1.length()) { 
		return s2.length();
	}
	if (!s2.length()) {
		return s1.length();
	}
	else {
		// Remove from s1
		int d = 1 + lDist( s1.substr(1,s1.length()-1), s2 );
		// Add to s1
		int a = 1 + lDist( s1, s2.substr(1,s2.length()-1) );
		// Replace in a
		int r = lDist( s1.substr(1,s1.length()-1), s2.substr(1,s2.length()-1) );
		int cost = s1[0] != s2[0]; 
		r += cost;

		return (d < a && d < r) ? d : ((a < r) ? a : r); 
	}
}

int main(int argc, char *argv[]) {
	string s1 = string(argv[1]);
	string s2 = string(argv[2]);
	cout << "L Distance b/w : " << s1 << " and " << s2 << " is : " << lDist(s1, s2) << "\n";
	return 0;
}
