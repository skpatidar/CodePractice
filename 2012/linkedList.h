#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> 		vInt;
typedef vector<int>::iterator 	vIntIter;

typedef struct linkedListNode {
	int data;
	struct linkedListNode * next;
}linkedListNode;

class linkedList {
	private :
		linkedListNode	*listHead;
	public :
		// http://cslibrary.stanford.edu/105/LinkedListProblems.pdf
		linkedListNode* returnHead() { return listHead; };
		linkedListNode* setHead(linkedListNode* _listHead) { listHead = _listHead; };
		void push(linkedListNode * newNode);
		linkedListNode* createNewNode(linkedListNode *prev, int data, linkedListNode *next);
		void printList();
		void printList(linkedListNode*);
		int length();		
		int count(int data);		
		void reverse();
		void recursiveReverse();
		linkedListNode* recursiveReverseList(linkedListNode *node, linkedListNode *prev);
		int  getNth(int n);
		linkedListNode* insertNth(int data, int n);
		linkedListNode* sortList();
		linkedListNode* mergeSort(linkedListNode*);
		linkedListNode* mergeLists(linkedListNode* a, linkedListNode* b);
		linkedListNode* midSplit(linkedListNode* head);
		linkedListNode* alternateSplit();
		void swapAdjacent();

		void deleteList();
		void deleteNode(linkedListNode*);
};

void linkedList::push(linkedListNode *newNode) {
	if (listHead == NULL) {
		listHead = newNode;
	} else {
		// Find Last Node on the List 
		linkedListNode * walk;
		walk = listHead;
		while (walk->next != NULL) { walk = walk->next; }
		walk->next = newNode; 
	}
}

void linkedList::printList(linkedListNode * head) {
	linkedListNode * walk;
	walk = head;
	while (walk != NULL) { 
		cout << "[ " << walk->data << " ] --> ";
		walk = walk->next; 
	}
	cout << "NULL\n";
}

void linkedList::printList() {
	linkedListNode * walk;
	walk = listHead;
	while (walk != NULL) { 
		cout << "[ " << walk->data << " ] --> ";
		walk = walk->next; 
	}
	cout << "NULL\n";
}
		
int linkedList::length() {
	int count = 0;
	for (linkedListNode *iter = listHead; iter != NULL; iter = iter->next) {
		count++;
	}
	return count;
}

int linkedList::count(int data) {
	linkedListNode *iter = listHead;
	int count = 0;
	while (iter != NULL) {
		if ( iter->data == data ) { 
			count++;
		}
	}
	return count;
}

void linkedList::reverse() {
	linkedListNode *previous = NULL;
	linkedListNode *next = NULL;
	while (listHead->next != NULL) {
		next = listHead->next;
		listHead->next = previous;
		previous = listHead;
		listHead = next;
	}
	listHead->next = previous;
}

void linkedList::recursiveReverse() {
	linkedListNode *node = listHead;
	listHead = recursiveReverseList(node, NULL);
}

linkedListNode* linkedList::recursiveReverseList(linkedListNode *node, linkedListNode *prev) {
	if (node->next == NULL) {
		node->next = prev;
		return node;
	} else {
		linkedListNode *temp = node->next;
		node->next = prev;
		return recursiveReverseList(temp, node);
	}
}

int linkedList::getNth(int n) {
	linkedListNode *iter = listHead;
	while (--n && iter != NULL) {
		iter = iter->next;
	}
	if (n) return -1;
	return iter->data;
}

linkedListNode* linkedList::createNewNode(linkedListNode *prev, int data, linkedListNode *next) {
	linkedListNode *newNode = new linkedListNode; 
	newNode->data = data;
	prev->next = newNode;
	newNode->next = next; 
	return newNode;
}
linkedListNode* linkedList::insertNth(int data, int n) {
	linkedListNode *iter = listHead;

	n--; // Find the last element after which to insert

	linkedListNode *prev = NULL;
	if (n==0) {
		linkedListNode *newNode = new linkedListNode; 
		newNode->next = listHead;
		newNode->data = data;

		listHead = newNode;
		return newNode;
	} else {
		while (--n && iter != NULL) {
			iter = iter->next;
			prev = iter;
		}
		if (n) return NULL;
		linkedListNode *newNode = createNewNode(prev, data, iter->next);
		return newNode;
	}
}

linkedListNode* linkedList::midSplit(linkedListNode* head) {
	if (head==NULL) return head;
	
	linkedListNode *midNode = head;
	linkedListNode *iter = head;
	
	while (1) {
		iter = iter->next;
		if (iter==NULL) break;
		iter = iter->next; 
		if (iter==NULL) break;
		midNode = midNode->next;
	}

	return midNode;
}

linkedListNode* linkedList::mergeLists(linkedListNode* a, linkedListNode* b) {
	if (a==NULL) return b;
	if (b==NULL) return a;

	linkedListNode *iterA = a, *iterB = b;
	linkedListNode *aPrev, *bNewTop, *bPrev, *aNewTop;
	linkedListNode *head = (a->data > b->data) ? b : a;	

	/* Non-Recursize */
	while( iterA != NULL && iterB != NULL) { 
		if (iterA->data <= iterB->data) {
			while(iterA->data <= iterB->data) { 
				aPrev = iterA;
				iterA = iterA->next;
				if (iterA==NULL) break;
			}
			bNewTop = iterB->next;
			aPrev->next = iterB; 
			if ( iterA != NULL ) {
				if ( iterB->next != NULL ) {
					if ( (iterB->next)->data > iterA->data ) {
						iterB->next = iterA;
					}
				} else {
					iterB->next = iterA;
				}
			} 
			iterB = bNewTop;
		} else {
			while(iterB->data <= iterA->data) { 
				bPrev = iterB;
				iterB = iterB->next;
				if (iterB==NULL) break;
			}
			aNewTop = iterA->next;
			bPrev->next = iterA; 
			if ( iterB != NULL ) {
				if ( iterA->next != NULL ) {
					if ( (iterA->next)->data > iterB->data ) {
						iterA->next = iterB;
					}
				} else {
					iterA->next = iterB;
				}
			}
			iterA = aNewTop;
		}
	}
	return head;
}

linkedListNode* linkedList::mergeSort(linkedListNode* head) {
	if (head == NULL) return NULL;
	if (head->next == NULL) return head; 
	
	// Create 2 lists to be sorted and merged later
	linkedListNode* midNode = midSplit(head);
	linkedListNode* firstHalf = head;
	linkedListNode* secondHalf = midNode->next;

	// Cut off first list 
	midNode->next = NULL;

	// Sort halves
	firstHalf = mergeSort(firstHalf);
	secondHalf = mergeSort(secondHalf);
	
	// Merge Halves
	linkedListNode* sortedListHead = mergeLists(firstHalf, secondHalf);

	//cout << "===========================\n";
	//printList(sortedListHead);
	//cout << "===========================\n";
	
	return sortedListHead;
}

linkedListNode* linkedList::sortList() {
	if (listHead == NULL) return NULL;
	listHead = mergeSort(listHead);	
}

linkedListNode* linkedList::alternateSplit() {
	linkedListNode* firstHead = listHead;
	linkedListNode* newHead = listHead->next;
	linkedListNode* secondHead = listHead->next;

	while (secondHead != NULL ) {
		firstHead->next = secondHead->next;
		firstHead = firstHead->next;
		if (firstHead) {
			secondHead->next = firstHead->next;
			secondHead = secondHead->next;
		} else {
			secondHead = firstHead;
		}
	}
	return newHead;
}

void linkedList::swapAdjacent() {
	if (listHead==NULL) return;

	linkedListNode *prev, *temp, *iterA, *iterB;

	prev = NULL;
	iterA = listHead;
	iterB = listHead->next;

	if (iterA && iterB) listHead = iterB; 
	
	while (iterA && iterB) {
		// Swap Pointers	
		temp = iterB->next;
		iterB->next = iterA;
		iterA->next = temp;
		if (prev) prev->next = iterB;
	
		// Pret for next loop
		prev = iterA;
		iterA = iterA->next;
		if (!iterA) break;
		iterB = iterA->next;
	}
}

void linkedList::deleteNode(linkedListNode* node) {
	if (node == NULL) return;
	deleteNode(node->next);
	cout << "Deleting node with data : " << node->data << "\n";
	delete node; 
	return;
}

void linkedList::deleteList() {
	deleteNode(listHead);
}
