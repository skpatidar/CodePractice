// Generate 'k' individually sorted dummy linked lists
// Merge all Linked Lists in O(n * log(k)) 
// n = total number of elements in all lists
// k = number of lists
#include <iostream>
#include <vector>
#include <iterator>
#include <stdlib.h>
#include <algorithm>

using namespace std;
// Linked List Node 
struct linkNode {
	int data;
	struct linkNode *next;
};
// Vector to Linked List convertor
linkNode* vecToList( vector<int> v ) {	// Vector of Size 1 and more
	vector<int>::iterator vIter;
	linkNode* head = new linkNode; 
	if (!head) { cout << "Can NOT allocate memory\n\nExiting..."; exit(1); }
	linkNode* node = head;
	node->data = *(v.begin());
	for (vIter = v.begin()+1; vIter != v.end(); vIter++) {
		node->next = new linkNode;
		if (!node->next) { cout << "Can NOT allocate memory\n\nExiting..."; exit(1); }
		node->next->data = *vIter;
		node = node->next;
	}
	node->next = NULL;
	return head;
}
// Misc Function : Random Numbers b/w 0 and 1023
int randMod1K() {
	return rand()%1024;
}
// Misc Function : Use with Heap for building MinHeap
bool descFunc( pair<int,int> a, pair<int,int> b ){
	if (a > b) { return 1; }
	return 0;
}
// Generate numLists random linked lists
vector<linkNode*> generateLinkedLists(int numLists) {
	vector<linkNode*> nLists;
	for ( int i=0; i < numLists; i++ ){
		int numElements = rand() % 5 + 1;
		vector<int> v(numElements);
		generate(v.begin(), v.end(), randMod1K);
		sort(v.begin(), v.end());
		linkNode* thisList = vecToList(v);
		nLists.push_back(thisList);
	}
	return nLists;
}
// Print a Linked List
void printList(linkNode* list) {
	while (list) {
		cout << list->data << "--->";
		list = list->next;
	}
	cout << "X\n";
}
// Main
int main( int argc, char* argv[]) { 
	if(argc < 2) { cout << "Usage : ./a.out NUM_LISTS\nExiting...\n"; return 1; }
	int numLists = atoi(argv[1]);
	if ( ! numLists ) { cout << "Enter nonZero number of lists\nExitin ...\n"; return 1;}

	srand(time(NULL));

	//Generate numLists random Linked Lists of Integers and Print
	vector<linkNode*> nLists;
	nLists = generateLinkedLists(numLists);
	vector<linkNode*>::iterator	listElement; 
	cout << numLists << " Linked Lists :\n";
	for ( listElement = nLists.begin(); listElement != nLists.end(); listElement++ ) {
		cout << "\t"; printList(*listElement);
	}

	// Make a heap of 'numLists' number of Elements : First element from each list
	// Heap of pairs of data and listId 
	int listId;
	vector<pair<int,int> >	tinyHeap;
	for ( listId=0, listElement = nLists.begin(); listElement != nLists.end(); listElement++, listId++ ) {
		pair<int,int> p((*listElement)->data, listId);
		tinyHeap.push_back(p);
		*listElement = (*listElement)->next;			// Point to next element which needs to be processed
	}

	// Heapify
	make_heap(tinyHeap.begin(), tinyHeap.end(), descFunc);

	vector<int> sortedList;
	listId = -1;	
	// Pop elements from Heap and Add a New Element from the same list
	// (or any other list if that list is empty)
	do {
		// Pop and add an element from heap to output sorted List 
		pop_heap(tinyHeap.begin(), tinyHeap.end(), descFunc);
		sortedList.push_back( (*(tinyHeap.end()-1)).first );
		listId = (*(tinyHeap.end()-1)).second;

		// Pick a new listId if current list is empty
		if (!(*(nLists.begin()+listId)) ) { 			// If the particular list has NO MORE elements
			listId = -1;
			for (int i=0; i < numLists; i++ ) {
				if ( (*(nLists.begin() + i)) ) {
					listId = i;			//Move until we have a non-empty List
					break;
				}
			}
		}

		// Add new element to heap and heapify unless all lists empty
		if ( listId >= 0 ) {	
			int newElement = (*(nLists.begin()+listId))->data;		// Take the data
			(*(nLists.begin()+listId)) = (*(nLists.begin()+listId))->next; 	// Move the Pointer for the List
			*(tinyHeap.end()-1) = make_pair(newElement, listId);		// Add the newElement to end of Heap
			push_heap(tinyHeap.begin(),tinyHeap.end(), descFunc);		// Heapify the last element
		}
	} while (listId >= 0);

	//Add all elements from the Heap to sorted list	
	vector<pair<int,int> >::iterator first, last;
	first = tinyHeap.begin(); 
	last = tinyHeap.end() - 1; 	// Last Pop from the do-While above is already recorded 
	while(first != last) {
		pop_heap(first, last, descFunc);
		sortedList.push_back( (*(last-1)).first );
		last--;
	}

	// Print sortedList
	cout << "\n\nMerged Sorted Linked List :\n";
	linkNode* mergedList = vecToList(sortedList);
	printList(mergedList);
	cout << "\n\n";
	return 0;
}
