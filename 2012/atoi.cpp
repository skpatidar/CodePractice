#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

int atoi(char *a) {
	int neg  = 0;
	if (*a == '-') {
		a++;
		neg = 1;
	}
	int num = 0;
	while ( (*a != '\0') ) {
		num = num * 10 + (*a - '0'); 
		a++;
	}
	if (neg) num *= -1;
	return num;
}

int main (int argc, char *argv[]) {
	char *a = "-1234512345\0";
	cout << "Number : " << atoi(a) << "\n";
}
