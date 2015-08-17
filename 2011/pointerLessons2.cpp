#include <iostream>

using namespace std;

class	Cat {
	public:
		Cat();
		~Cat();

	private :
		int age;
};

Cat::Cat() {
	cout << "Calling constructor\n";
	age = 1;
}
Cat::~Cat() {
	cout << "Calling destrutor\n";
}

int main () {
	unsigned short shortVar = 5;
	unsigned long  longVar = 65555;
	long sVar = -65555;

	cout << "ShortVar: \t" << shortVar << "\t" << &shortVar << "\n";
	cout << "LongVar: \t" << longVar << "\t" << &longVar << "\n";
	cout << "sVar: \t" << sVar << "\t" << &sVar << "\n";
	
	//printVarData(shortVar);
	//printVarData(longVar);
	//printVarData(sVar);

	unsigned long *pLong = new unsigned long;
	unsigned long vLong = 12121212;
	cout << "pLong : \t" << *pLong << "\t" << pLong << "\n";
	delete pLong;
	pLong = &vLong;
	cout << "pLong : \t" << *pLong << "\t" << pLong << "\n";
	
	Cat	stackCat;
	Cat	*heapCat = new Cat;
	delete heapCat;
	return 0;
}

