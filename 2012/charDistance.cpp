#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <map>
#include <algorithm>

using namespace std;

typedef vector<int> 		vInt;
typedef vector<int>::iterator 	vIntIter;

string charDistance(string s, int dist) {
	map<char, int> h;
	map<char, int> d;

	string rearr = "";

	for (string::iterator iter=s.begin(); iter != s.end(); iter++) {
		h[*iter]++;
		d[*iter] = dist;
	}
	cout << "Map : \n";
	for (map<char, int>::iterator iter=h.begin(); iter != h.end(); iter++) {
		cout << "\t" << (*iter).first << " : " << (*iter).second << "\n";
	}
	
	while (!h.empty()) {
		// Pick the guy with max vlaue 
		char cur; 
		int maxFreq = -1;
		for (map<char, int>::iterator iter=h.begin(); iter != h.end(); iter++) {
			if ( (*iter).second > maxFreq && d[(*iter).first] >= dist ) {
				cur = (*iter).first;
				maxFreq = (*iter).second;
			}
		}
		if (maxFreq < 0) { 
			cout << "Can't rearrange\n";
			break;
		}
		h[cur]--;
		if (h[cur] == 0) {
			h.erase(cur);
		}
		d[cur] = 1;
		for (map<char, int>::iterator iter=h.begin(); iter != h.end(); iter++) {
			if ( (*iter).first != cur ) {
				d[(*iter).first]++;
			}
		}
		cout << "Pick char : " << cur << " with frequency " << maxFreq << "\n";
		rearr += cur;
		
		cout << "Current Map : \n";
		for (map<char, int>::iterator iter=h.begin(); iter != h.end(); iter++) {
			cout << "\t" << (*iter).first << " : " << (*iter).second << "\n";
		}
		cout << "Current Rearranged : " << rearr << "\n";
	}
	
	return rearr;
}

int main (int argc, char *argv[]) {
	string s = "aaabbcc";
	int dist = 3;

	string rearr = charDistance(s, dist);
	cout << "Rearranged : " << rearr << "\n";
}
