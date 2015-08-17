//
//
//


#include <iostream>
#include <list>
#include "lolCatLinkedList.h"

using namespace std;

int main () {
	cout << "Lets build a linked list of LOL CATs\n";

	ListNode * pNode = 0;
	LolCat * pCat = new LolCat(0);
	int age;

	list<LolCat *> stlList;
	ListNode *pHead = new ListNode(pCat);

	const int	kCatCount = 10;
	for ( int age = kCatCount; age >= 0  ; age-- ) {
		cout << "Adding a cat with age " << age << "\n";
		pCat = new LolCat(age);	

		stlList.push_back(pCat);

		pNode = new ListNode(pCat);
		pHead->Insert(pNode);
	}

	cout << "printing stllist ... \n";
	for (list<LolCat*>::iterator iter=stlList.begin(); iter != stlList.end(); iter++ ) {
		cout << "Cat's age is : " << (*iter)->GetAge() <<"\n";
	}

	pHead->Display();
	delete pHead;

	cout << "exiting ...\n";

	return 0;
}
