#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <stack>

using namespace std;

typedef vector<int> 		vInt;
typedef vector<int>::iterator 	vIntIter;

void isPalindrome(unsigned int n) {
	if ( n < 10 ) {
		cout << "Palindrome\n"; 
		return;
	}

	int right = n % 10; 

	int copy = n / 10; 
	stack<int> digits;
	int digit;
	while (copy) {
		digit = copy % 10;
		digits.push(digit);
		copy /= 10;
	}
	int left = digits.top();
	digits.pop();

	//Recreate remaining int
	unsigned int reducedN = 0;
	unsigned int d;

	while (!digits.empty()) {
		d = digits.top();
		digits.pop();
		reducedN = reducedN * 10 + d;
	}

	if (left != right) {
		cout << "Not a Palindrome\n";
		return;
	}
	else {
		cout << "Reduced N : " << reducedN << "\n";
		isPalindrome(reducedN);
	}
}

int main (int argc, char *argv[]) {
	if (argc < 2) { 
		cout << "Provide nElements on commandline \nExiting\n"; exit(0); 
	} 
	unsigned int n = atoi(argv[1]);

	isPalindrome(n);
	return 0;
}
