#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

bool isSubString(string X, string Y) {
	int xLen = X.length();
	int yLen = Y.length();

	if (!xLen) return 1;
	if (!yLen) return 0;

	int xi = 0 , yi = 0;
	while ( yi < yLen ) {
		xi = 0;
		int yDash = yi;
		while ( xi < xLen && yDash < yLen ) {
			if (X[xi] == Y[yDash]) {
				xi++;
				yDash++;
			} else {
				break;
			}	
		}
		if ( xi == xLen ) { return 1; }
		if ( yDash == yLen ) { return 0; }
		yi++;
	}
	return 0;
}

char* isSubString2(char *x, char *y) {
	while (*y != '\0') {
		char* xDash = x;
		char* yDash = y;
		while ( *xDash != '\0' && (*xDash == *yDash) ) {
			xDash++;
			yDash++;
		}
		if (*xDash == '\0') return y;
		y++;
	}
	return '\0';
}

int main (int argc, char *argv[]) {
	char *x = "bada\0";
	char *y = "abrakadabadara\0";

	string A = "bada";
	string B = "abrakadabadara";
	cout << "Is SubString : " << isSubString(A, B) << "\n";
	cout << "Sub String starts : " << isSubString2(x, y) << "\n";
}
