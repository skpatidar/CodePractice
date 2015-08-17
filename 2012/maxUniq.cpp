#include<iostream>
#include<vector>
#include<stdlib.h>
#include<math.h>
#include<string>
#include<algorithm>
#include<iterator>

using namespace std;

string maxUniq(string s) {
	bool exists[26] = {0};
	int len = s.length();
	int start = 0, end = 0, length=0;
	int maxStart = 0, maxEnd = 0, maxLength = 0;
	while ( end < len ) {
		if ( exists[s[end] - 'a'] ) { 
			if ( maxLength < length ) {
				cout << "MaxLen, start and end : " << length << ", " << start << ", " << (end - 1)  << "\n";
				maxLength = length;
				maxStart = start;
				maxEnd = end - 1;	
			}
			int temp = start;
			while(s[temp] != s[end] && temp < len) { temp++; exists[s[temp]-'a']=0;}
			start = temp + 1;
			length = end - start + 1;
			end++;
		} else { 
			exists[s[end] - 'a'] = 1;	
			end++;
			length++;
		}	
	}
	if ( maxLength < length ) {
		cout << "MaxLen, start and end : " << length << ", " << start << ", " << (end - 1)  << "\n";
		maxLength = length;
		maxStart = start;
		maxEnd = end - 1;	
	}
	return s.substr(maxStart,maxLength);
}

int main(int argc, char *argv[]) {
	string s(argv[1]);
	cout << "Max Uniq String in " << s << " is " << maxUniq(s) << "\n";
	return 0;
}
