#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <math.h>

using namespace std;

typedef vector<int> 		vInt;
typedef vector<int>::iterator 	vIntIter;

string minSubString(string str, string subSet) {
	map<char, int> needToFind;
	map<char, int> hasFound;

	int strLength = str.size();
	int setLength = subSet.size();

	for (char c = 'a'; c <= 'z'; c++) { hasFound[c] = needToFind[c] = 0; }
	for (int i=0; i < setLength; i++) { needToFind[subSet[i]]++;         }

	int count = 0, iter = 0, begin = 0, end = 0;
	int minWindowLen = INT_MAX, minWindowBegin = INT_MAX, minWindowEnd = INT_MAX;

	for (int begin=0, end=0; end < strLength; end++ ) {
		char curChar = str[end];
		// Skip chars not in T
		if ( !needToFind[curChar] ) continue;

		hasFound[curChar]++;

		// Register if useful char to build up the window
		if(hasFound[curChar] <= needToFind[curChar]) 
			count++;

		if (count == setLength) { // Minimize the window size by moving begin towards end
			while ( needToFind[str[begin]]==0 || needToFind[str[begin]] < hasFound[str[begin]] ) 
			{
				if ( hasFound[str[begin]] > needToFind[str[begin]] )
					hasFound[str[begin]]--;
				begin++;
			}
			int winLen = end - begin + 1;
			if (winLen < minWindowLen) { 
				minWindowLen = winLen;
				minWindowBegin = begin;
				minWindowEnd = end;
			}
		}
	}
	cout << "Window Length : " << minWindowLen << "\n\tWindow Begin : " << minWindowBegin << "\n\tWindow End " << minWindowEnd << "\n";
	if (count != setLength) 
		return "";
	
	return str.substr(minWindowBegin, minWindowLen);
}

int main (int argc, char *argv[]) {
	if (argc < 3) { 
		cout << "Provide string and subSet on commandline \nExiting\n"; exit(0); 
	} 

	string str(argv[1]);
	string subSet(argv[2]);

	cout << "Min Lenght SubString of chars - " << subSet << " - in string : " << str << " is : " << minSubString(str, subSet) << "\n";
}
