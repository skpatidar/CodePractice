#include "binTree.h"

void printPathsRecur(treeNode *curRoot, int paths[], int pathLen) {
	if (curRoot == NULL) { return; } 

	paths[pathLen] = curRoot->data;
	pathLen++;

	if (curRoot->left == NULL && curRoot->right == NULL) { 
		printArray(paths, pathLen);
	} else {
		printPathsRecur(curRoot->left, paths, pathLen);
		printPathsRecur(curRoot->right, paths, pathLen);
	}
}

int randMod1k() { return rand() % 1024; }

int main (int argc, char *argv[]) {
	if (argc < 2) { cout << "Provide nElements on commandline \nExiting\n"; exit(0); } 
	srand(time(NULL));

	int nElements = atoi(argv[1]);
	vInt		v(nElements);
	vIntIter 	iBegin = v.begin();
	vIntIter	iEnd = v.end();
	generate(iBegin, iEnd, randMod1k);

	//sort(iBegin, iEnd);

	// Create binary tree with above vector
	binTree * treePointer = new binTree; 

	for (vIntIter walk = iBegin; walk != iEnd; walk++) {	
		cout << "Add data = " << *walk << " to the tree\n";
		treePointer->rootNode = treePointer->addToTree(treePointer->rootNode, *walk);
	}

/*	// Created balanced BST out of a sorted array
	sort(iBegin, iEnd);
	for (vIntIter walk = iBegin; walk != iEnd; walk++) {
		cout << "Add data = " << *walk << " --> ";
	}
	treePointer->rootNode = treePointer->createBSTfromSortedArray(v);
*/

	cout << "\nPretty Print Tree  : \n";
	treePointer->prettyPrintTree(treePointer->rootNode);

	// Print Tree 
	cout << "Pre Order : ";
	treePointer->printTreePreOrder(treePointer->rootNode);
	cout << "\n\n";

	cout << "In Order : ";
	treePointer->printTreeInOrder(treePointer->rootNode);
	cout << "\n\n";

	cout << "In Order (non-Rec) : ";
	treePointer->printTreeInOrderNonRec(treePointer->rootNode);
	cout << "\n\n";
	
	cout << "Max Depth (Iter) : ";
	treePointer->maxDepthIter(treePointer->rootNode);
	cout << "\n\n";

	cout << "Max Depth (Iterative) : ";
	treePointer->maxDepthIterative(treePointer->rootNode);
	cout << "\n\n";

	cout << "Post Order : ";
	treePointer->printTreePostOrder(treePointer->rootNode);
	cout << "\n\n";
	
	cout << "Print tree in ZigZag Order  : \n";
	treePointer->printZigZagOrder(treePointer->rootNode);
	
	cout << "Print tree in Level Order  : \n";
	treePointer->printLevelOrder(treePointer->rootNode);

/*
	cout << "Size of the tree in # of Nodes " << treePointer->size(treePointer->rootNode) << "\n";
	cout << "Max depth of the tree in # of Nodes " << treePointer->maxDepth(treePointer->rootNode) << "\n";
	cout << "Min Value in the tree " << treePointer->minValue(treePointer->rootNode) << "\n";
	
	cout << "Print Paths : \n";
	treePointer->printPaths(treePointer->rootNode);
	cout << "\n";
*/

	/*cout << "Mirror the Tree : \n";
	treePointer->mirror(treePointer->rootNode);
	treePointer->printTreeInOrder(treePointer->rootNode);
	*/

/*
	cout << "Print tree in Level Order  : \n";
	treePointer->printLevelOrder(treePointer->rootNode);
	
	cout << "Pretty Print Tree  : \n";
	treePointer->prettyPrintTree(treePointer->rootNode);
*/	
	//int data = treePointer->minValue(treePointer->rootNode); 
	//cout << "Invert Tree by Leaf : " << data << "\n";
	//treePointer->invertTreeByLeaf(treePointer->rootNode, data);
	//cout << "Pretty Print Tree  : \n";
	//treePointer->prettyPrintTree(treePointer->rootNode);

	/*
	cout << "Tree to list : \n";
	treeNode *linkHead = treePointer->treeToList(treePointer->rootNode);
	cout << "Print the Double Linked List : \n";	
	treePointer->printLinkedList(treePointer->rootNode);
	*/

	return 0;
}
