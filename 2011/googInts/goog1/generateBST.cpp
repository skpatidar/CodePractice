
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

int randMod1K() { return rand()%1024; }

struct treeNode {
	int	data;
	struct treeNode *left;
	struct treeNode *right;
};

treeNode* generateBST(vector<int>::iterator begin, vector<int>::iterator end) {
	if ( end - begin < 1 ) {
		treeNode *tNode = new treeNode;
		tNode->data = *begin;
		tNode->left = tNode->right = NULL;
		return tNode;
	}

	vector<int>::iterator middle = begin + (end - begin)/2;
	treeNode *tNode = new treeNode;
	tNode->data = *middle;
	if ( middle - begin > 0 ) {
		tNode->left = generateBST(begin, middle-1);
	}
	if ( end - middle > 0 ) {
		tNode->right = generateBST(middle+1, end);
	}
	return tNode;
}
void printBST(treeNode *tNode) {
	if(!tNode) { return; }
	printBST(tNode->left);
	cout << tNode->data << ", ";
	printBST(tNode->right);
}
int main (int argc, char *argv[]) {
	if ( argc < 2 ) { 
		cout << "Provide # of elements :./a.out #\nExiting ....\n"; 
		return 1; 
	}

	int n = atoi(argv[1]);
	vector<int>	vI(n);
	
	vector<int>::iterator	aBegin = vI.begin();
	vector<int>::iterator	aEnd = vI.end();
	srand(time(NULL));
	generate(aBegin, aEnd, randMod1K);
	sort(aBegin, aEnd);

	cout << "Array sorted : \n";
	copy (aBegin, aEnd, ostream_iterator<int>(cout,", "));
	cout << "\n";

	treeNode *rootNode = generateBST(aBegin, aEnd - 1);
	printBST(rootNode);

	return 0;
}
