//
// Header
//
#include <iostream>
using namespace std;

class LolCat {
public: 
	LolCat() { age = 1; }
	LolCat( int _age ):age(_age){}
	int	GetAge () const { return age; }
private:
	int age;
};

class ListNode {
public:
	ListNode(LolCat*);
	~ListNode();

	LolCat* GetCat() const { return itsCat; }
	void SetNext(ListNode *node) {itsNext = node;}
	void Insert(ListNode *);
	void Display();
private:
	LolCat * itsCat;
	ListNode * itsNext;
};

ListNode::ListNode(LolCat * pCat):itsCat(pCat),itsNext(NULL){}

ListNode::~ListNode() {
	cout << "Deleting node ...\n";
	delete itsCat;
	itsCat = NULL;
	delete itsNext;
	itsNext = NULL;
}

void ListNode::Insert( ListNode * newNode ) {
	if (!itsNext) {
		itsNext = newNode;
	} else {	
		int nextNodeAge = itsNext->GetCat()->GetAge();
		int thisNodeAge = itsCat->GetAge();
		int newNodeAge = newNode->GetCat()->GetAge();

		if ( newNodeAge >= thisNodeAge && newNodeAge < nextNodeAge ) {
			newNode->SetNext(itsNext);
			itsNext = newNode;
		}
		else {
			itsNext->Insert(newNode);
		}
	}
}

void ListNode::Display() {
	cout << "My cat is ";
	cout << itsCat->GetAge() << " yeears old\n";
	if (itsNext) {
		itsNext->Display();
	}
}
