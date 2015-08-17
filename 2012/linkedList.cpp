#include "linkedList.h"

int randMod1k() { return rand() % 1024; }

int main (int argc, char *argv[]) {
	if (argc < 2) { cout << "Provide nElements on commandline \nExiting\n"; exit(0); } 
	srand(time(NULL));

	int nElements = atoi(argv[1]);

	vInt	v(nElements);
	vIntIter iBegin = v.begin();
	vIntIter iEnd = v.end();

	generate(iBegin, iEnd, randMod1k);

	// Generate Linked List with above vector 
	linkedList * listPointer = new linkedList; 

	for ( vIntIter walk = iBegin; walk != iEnd; walk++ ) {	
		cout << "Add data = " << *walk << " to the linked list\n";
		linkedListNode *newNode = new linkedListNode;
		newNode->data = *walk;
		newNode->next = NULL;
		listPointer->push(newNode);
	}

	//Print the linked List 
	cout << "Printing the linked list \n";
	listPointer->printList();

	cout << "Length of linked list : " << listPointer->length() << "\n";
	
	cout << "Reverse the list \n";
	listPointer->reverse();
	listPointer->printList();
	cout << "Re-Reverse the list \n";
	listPointer->recursiveReverse();
	listPointer->printList();

/*
	cout << "Get 7th Element : " << listPointer->getNth(7) << "\n";
	cout << "Get 3rd Element : " << listPointer->getNth(3) << "\n";
	cout << "Get 17th Element : " << listPointer->getNth(17) << "\n";
	cout << "Insert 7th Element as 888 : " << (listPointer->insertNth(888, 7))->data << "\n";
	listPointer->printList();
	cout << "Insert 1st Element as 999 : " << (listPointer->insertNth(999, 1))->data << "\n";
	listPointer->printList();
	cout << "Insert 124th Element as 666 : ";
	linkedListNode *temp = (listPointer->insertNth(666, 124));
	if (temp) cout << temp->data << "\n";
	else cout << "-1\n";
	listPointer->printList();
*/

/*
	// [ 429 ] --> [ 524 ] --> [ 699 ] --> [ 760 ] --> [ 829 ] --> NULL
	// [ 94 ] --> [ 140 ] --> [ 432 ] --> [ 765 ] --> NULL

	linkedList *sortListOne = new linkedList;
	linkedList *sortListTwo = new linkedList;
	
	int oneArr[] = {429, 524, 699, 760, 829};
	int sizeOne = 5;
	int twoArr[] = {94, 140, 432, 765};
	int sizeTwo = 4;
	// Merge Sorted Lists 
	for ( int i = 0; i < sizeOne; i++ ) {
		linkedListNode *newNode = new linkedListNode;
		newNode->data = oneArr[i];
		newNode->next = NULL;
		sortListOne->push(newNode);
	}
	for ( int i = 0; i < sizeTwo; i++ ) {
		linkedListNode *newNode = new linkedListNode;
		newNode->data = twoArr[i];
		newNode->next = NULL;
		sortListTwo->push(newNode);
	}
	
	cout << "List One : \n";
	sortListOne->printList();

	cout << "\nList Two : \n";
	sortListTwo->printList();

	linkedListNode* mergeHead = sortListOne->mergeLists(sortListOne->returnHead(), sortListTwo->returnHead());
	linkedList *mergeList = new linkedList;
	mergeList->setHead(mergeHead);
	mergeList->printList();

*/
	//linkedListNode* midPoint = listPointer->findMidNode(listPointer->returnHead());
	//cout << "Mid Point Data : " << midPoint->data << "\n";

	cout <<"\nSorted List :\n";
	listPointer->sortList();
	listPointer->printList();

/*
	cout <<"\nAlternate Split :\n";
	linkedListNode * newHead = listPointer->alternateSplit();
	listPointer->printList();
	listPointer->printList(newHead);
*/
	cout << "Swap adjacent nodes\n";
	listPointer->swapAdjacent();
	listPointer->printList();
	
	cout << "Deleting the list \n";
	listPointer->deleteList();

	return 0;
}
