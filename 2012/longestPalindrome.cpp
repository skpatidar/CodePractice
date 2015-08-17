#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

typedef vector<int> 		vInt;
typedef vector<int>::iterator 	vIntIter;

string findPalindromeAt(string s, int pivot, int plusOne) {
	int goLeft, goRight;

	if (plusOne) {
		goLeft = pivot;
		goRight = pivot + 1;
	} else {
		goLeft = pivot - 1;
		goRight = pivot + 1;
	}

	while ( goLeft >= 0 && goRight < s.length()) {
		if ( s[goLeft] != s[goRight] ) {
			break;
		}
		goRight++;
		goLeft--;
	}
	goLeft++;
	goRight--;

	string palin; 
	if (goLeft <= goRight) {
		palin = s.substr(goLeft, goRight-goLeft+1);
	}

	return palin;
}

int longestPalindrome(string s) {
	int size = s.length();
	cout << "String : " << s << "\n" << "String length : " << size << "\n";
	
	string longestPalindrome; 
	
	for ( int pivot = 0; pivot < size; pivot++ ) {
		for ( int plusOne = 0; plusOne <= 1; plusOne++ ) {
			string palindrome = findPalindromeAt(s, pivot, plusOne);
			cout << "Longest Palindrom @ " << pivot << " with plusOne = " << plusOne << " is : " << palindrome << "\n";
			if (palindrome.length() > longestPalindrome.length()) {
				longestPalindrome = palindrome;
			}
		}
	}
	cout << "Longest Palindrome SubString : " << longestPalindrome << "\n";
	return longestPalindrome.length();
}

int main (int argc, char *argv[]) {
	if (argc < 2) { 
		cout << "Provide nElements on commandline \nExiting\n"; exit(0); 
	}

	string s(argv[1]);

	cout << "Length of longest substring palindrome : " << longestPalindrome(s) << "\n";

	return 0;
}
