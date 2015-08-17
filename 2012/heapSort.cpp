#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <iterator> 

using namespace std;

typedef vector<int> 		vInt;
typedef vector<int>::iterator 	vIntIter;

int randMod100() { return rand() % 100; }

typedef struct heapNode {
	int data;
	struct heapNode* cOne;
	struct heapNode* cTwo;
} heapNode;

class heap {
	private :
		vector<int>	arrHeap;
		int 		size;

	public :
		heap(int);

		void insert(int data);
		int pop(); 
		void heap::sort();

		void pushDown(int);
		void pushUp(int);
};

void heap::insert(int data) {
	arrHeap.push_back(data);
	size++;
	pushUp(size-1);
}

int heap::pop() {
	int min = arrHeap[0];
	arrHeap[0] = arrHeap[size-1];
	size--;
	pushDown(0);
	return min;
}

void heap::pushUp ( int n ) {
	while( n > 0 ) {
		if (arrHeap[(n-1)/2] > arrHeap[n] ) {
			int temp = arrHeap[n];
			arrHeap[n] = arrHeap[(n-1)/2];
			arrHeap[(n-1)/2] = temp;
			n = (n-1) / 2;
		} else {
			return;
		}
	}
}

void heap::pushDown( int n ) {
	while ( (n*2 + 1) < size ) {
		if ( n*2 + 2 < size ) {
			if ( arrHeap[n] > arrHeap[n*2+1] || arrHeap[n] > arrHeap[n*2+2] ) {
				// The node is defying Min Heap property
				if ( arrHeap[n*2+1] < arrHeap[n*2+2] ) {
					int temp = arrHeap[n*2+1];
					arrHeap[n*2+1] = arrHeap[n];
					arrHeap[n] = temp;
					n = n*2 + 1;
				} else {
					int temp = arrHeap[n*2+2];
					arrHeap[n*2+2] = arrHeap[n];
					arrHeap[n] = temp;
					n = n*2 + 2;
				}
			} else {
				return;
			}
		} else if ( arrHeap[n] > arrHeap[n*2+1] ) {
			int temp = arrHeap[n*2+1];
			arrHeap[n*2+1] = arrHeap[n];
			arrHeap[n] = temp;
			n = n*2 + 1;
		} else {
			return;
		}
	}
}

heap::heap(int n) {
	size = n;
	arrHeap.resize(n);
	generate(arrHeap.begin(), arrHeap.end(), randMod100);
	
	cout << "\n\nHeap Initialized : "; 
	copy(arrHeap.begin(), arrHeap.end(), ostream_iterator<int>(cout, " "));
	
	// Create a heap by adjusting the nodes
	for ( int i = size/2 - 1; i >= 0; i-- ) {
		pushDown(i);	
	}

	cout << "\n\nHeap Created : "; 
	copy(arrHeap.begin(), arrHeap.end(), ostream_iterator<int>(cout, " "));
	cout << "\n";
}

void heap::sort() {

	for (int i=0; i < 10; i++) { 
		insert(rand()%100);
	}

	cout << "Sorted : ";
	while (size) { 
		cout << pop() << " ";
	}
	cout << "\n";
}

int main (int argc, char *argv[]) {
	if (argc < 2) { 
		cout << "Provide nElements on commandline \nExiting\n"; exit(0); 
	} 
	srand(time(NULL));

	int n = atoi(argv[1]);

	heap h(n);
	h.sort();
}
