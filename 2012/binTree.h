#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <stack>
#include <math.h>

using namespace std;

typedef vector<int> 		vInt;
typedef vector<int>::iterator 	vIntIter;
typedef struct treeNode {
	int data;
	struct treeNode * left;
	struct treeNode * right;
}treeNode;

#define	MAX_WIDTH 160

void printPathsRecur(treeNode *curRoot, int paths[], int pathLen);

class binTree {
	private :
	public :
		treeNode	*rootNode;

		treeNode * addToTree(treeNode *curRoot, int data);

		void printTreePreOrder(treeNode *curRoot);
		void printTreeInOrder(treeNode *curRoot);
		void printTreeInOrderNonRec(treeNode *curRoot);
		void printTreePostOrder(treeNode *curRoot);

		int size(treeNode *curRoot); 
		int maxDepth(treeNode *curRoot); 	
		int maxDepthIter(treeNode *curRoot); 	
		int maxDepthIterative(treeNode *curRoot); 	

		int minValue(treeNode *curRoot);
		int hasPathSum(treeNode *curRoot, int sum);
		void printPaths(treeNode *curRoot);
		treeNode*  mirror(treeNode *curRoot);
		void doubleTree(treeNode *curRoot);
		void sameTree(treeNode *treeOne, treeNode *treeTwo);
		void countTrees(treeNode *curRoot);
		void printLevelOrder(treeNode *curRoot);
		void printZigZagOrder(treeNode *curRoot);
		treeNode*  invertTreeByLeaf(treeNode*, int );
		void prettyPrintTree(treeNode *curRoot);
		treeNode* treeToList(treeNode *curRoot);
		void printLinkedList(treeNode *curRoot);
		treeNode* join(treeNode* a, treeNode* b); 
		treeNode* append(treeNode* a, treeNode* b); 
		treeNode * createBSTfromSortedArray(vector<int> v);
		treeNode * createNode(int );
};

treeNode * newNode(int _data) {
	treeNode * newNode = new treeNode;
	newNode->data = _data;
	newNode->left = newNode->right = NULL;
	return newNode;
}

treeNode * binTree::addToTree(treeNode * curRoot, int _data) {
	if (curRoot == NULL) {
		curRoot = newNode(_data);
		return curRoot;
	} else {
		if ( _data < curRoot->data ) {
			curRoot->left = addToTree(curRoot->left, _data); 
		} else if ( _data > curRoot->data ) {
			curRoot->right = addToTree(curRoot->right, _data); 
		}
		else {
			cout << "Trying to add an element which exists\n";
		}
	}
	return curRoot;
}

void binTree::printTreePreOrder(treeNode * curRoot) {
	if (curRoot == NULL) { 
		return;
	} else {
		cout << "[" << curRoot->data << "] -- ";
		printTreePreOrder(curRoot->left);
		printTreePreOrder(curRoot->right);
	}
}

void binTree::printTreeInOrder(treeNode * curRoot) {
	if (curRoot == NULL) { 
		return;
	} else {
		printTreeInOrder(curRoot->left);
		cout << "[" << curRoot->data << "] -- ";
		printTreeInOrder(curRoot->right);
	}
}

void binTree::printTreeInOrderNonRec(treeNode * curRoot) {
	stack<treeNode*> S; 
	set<treeNode*> V; 
	
	S.push(curRoot);
	V.insert(curRoot);

	while(!S.empty()) {
		treeNode * top = S.top();
		if ( top->left && (V.find(top->left) == V.end()) ) {
			S.push(top->left);
			V.insert(top->left);
		} else {
			cout << "[" << top->data << "] -- ";
			S.pop();
			if ( top->right && (V.find(top->right) == V.end()) ) {
				S.push(top->right);
				V.insert(top->right);
			}
		}
	}
}

void binTree::printTreePostOrder(treeNode * curRoot) {
	if (curRoot == NULL) { 
		return;
	} else {
		printTreePostOrder(curRoot->left);
		printTreePostOrder(curRoot->right);
		cout << "[" << curRoot->data << "] -- ";
	}
}

int binTree::size(treeNode *curRoot) { 
	if (curRoot == NULL) {
		return 0;
	} else { 
		return 1 + size(curRoot->left) + size(curRoot->right);
	}
}

int binTree::maxDepth(treeNode *curRoot) {
	if (curRoot == NULL) {
		return 0;
	} else {
		return 1 + max( maxDepth(curRoot->left), maxDepth(curRoot->right) );
	}
}

int binTree::maxDepthIter(treeNode *curRoot) {
	if (curRoot == NULL) return 0;

	stack<treeNode*> S; 
	set<treeNode*> V; 
	
	S.push(curRoot);
	V.insert(curRoot);

	int maxDepth = 1;
	int tempDepth = 1;
	while(!S.empty()) {
		treeNode * top = S.top();
		if ( (top->right && (V.find(top->right) == V.end()) ) || ( top->left && (V.find(top->left) == V.end()) ) ) {
			if (top->right && (V.find(top->right) == V.end()) ) {
				S.push(top->right);
				V.insert(top->right);
				//cout << "Push Right Data : " << top->right->data << "\n";
			} 
			if ( top->left && (V.find(top->left) == V.end()) ) {
				S.push(top->left);
				V.insert(top->left);
				//cout << "Push Left Data : " << top->left->data << "\n";
			}
			tempDepth++;
		} else {
			cout << "[" << top->data << "] -- ";
			S.pop();
			if ( !top->right && !top->left ) {
				if (maxDepth < tempDepth) maxDepth = tempDepth;
				cout << "Leaf Node : " << top->data << " Pop-ed  - Depth = " << tempDepth << "\n";
				tempDepth--;
			}
		}
	}
	cout << "\nMax Depth : " << maxDepth << "\n";
}

int binTree::maxDepthIterative(treeNode *root) {
	if (!root) return 0;
	stack<treeNode*> s;
	s.push(root);
	int maxDepth = 0;
	treeNode *prev = NULL;
	while (!s.empty()) {
		treeNode *curr = s.top();
		if (!prev || prev->left == curr || prev->right == curr) {
			if (curr->left)
				s.push(curr->left);
			else if (curr->right)
				s.push(curr->right);
		} else if (curr->left == prev) {
			if (curr->right)
				s.push(curr->right);
		} else {
			s.pop();
			cout << "[" << curr->data << "] -- ";
		}
		prev = curr;
		if (s.size() > maxDepth)
			maxDepth = s.size();
	}
	cout << "\nMax Depth : " << maxDepth << "\n";
	return maxDepth;
}

int binTree::minValue(treeNode *curRoot) {
	if (curRoot->left == NULL) {
		return curRoot->data;
	} else {
		return minValue(curRoot->left);
	}
}

int binTree::hasPathSum(treeNode *curRoot, int sum) {
	
}

void printArray(int arr[], int len){
	cout << "Path : "; 
	for (int i=0; i < len; i++) {
		cout << arr[i] << " --> ";
	}
	cout << "NULL\n";
}


void binTree::printPaths(treeNode *curRoot) {
	int paths[1024];
	int pathLen = 0;
	if (curRoot == NULL) {
		return;
	}	
	printPathsRecur(curRoot, paths, pathLen);
}

treeNode* binTree::mirror(treeNode *curRoot) {
	if (curRoot == NULL) { return NULL; } 

	treeNode * tempPtr = curRoot->left;
	curRoot->left = mirror(curRoot->right);
	curRoot->right = mirror(tempPtr);

	return curRoot; 
}

void binTree::doubleTree(treeNode *curRoot) {
}

void binTree::sameTree(treeNode *treeOne, treeNode *treeTwo) {
}

void binTree::countTrees(treeNode *curRoot) {
}

void binTree::printZigZagOrder(treeNode *curRoot) {
	stack<treeNode*>	levelNodes;
	stack<treeNode*>	nextLevelNodes;
	int direction = 1;
	levelNodes.push(curRoot);
	while(!levelNodes.empty() || !nextLevelNodes.empty()) { 
		treeNode* curNode;
		if (direction) {
			curNode = levelNodes.top();
			levelNodes.pop();
		} else {
			curNode = nextLevelNodes.top();
			nextLevelNodes.pop();
		}
		cout << curNode->data << " -- ";
		if (direction) {
			if (curNode->right) { nextLevelNodes.push(curNode->right); }
			if (curNode->left) { nextLevelNodes.push(curNode->left); }
		} else {
			if (curNode->left) { levelNodes.push(curNode->left); }
			if (curNode->right) { levelNodes.push(curNode->right); }
		}
		if ( (direction && levelNodes.empty()) || (!direction && nextLevelNodes.empty()) ) {
			cout << "\n";
			direction  = 1 - direction;
		}
	}
	return;
}

void binTree::printLevelOrder(treeNode *curRoot) {
	queue<treeNode*>	levelNodes;
	queue<treeNode*>	nextLevelNodes;
	levelNodes.push(curRoot);
	while(!levelNodes.empty()) { 
		treeNode* curNode = levelNodes.front();
		levelNodes.pop();
		cout << curNode->data << " -- ";
		if (curNode->left) { nextLevelNodes.push(curNode->left); }
		if (curNode->right) { nextLevelNodes.push(curNode->right); }
		if (levelNodes.empty()){
			cout <<"\n";
			while( !nextLevelNodes.empty() ) {
				levelNodes.push(nextLevelNodes.front());
				nextLevelNodes.pop();
			}
		}
	}
	return;
}

void printPrettyLevel(int i, vector<int> levelData) {
	//cout << "Print Level : #i = " << i << "\n";
	int nodeGap = (int) (MAX_WIDTH / pow((double)2.0, (double)i)); 

	for (int i=0; i < nodeGap/2; i++) { cout << " "; }
	for (vIntIter vIter = levelData.begin(); vIter != levelData.end(); vIter++) {
		if (*vIter) cout << *vIter << "\t";
		for (int i=0; i < nodeGap; i++) { cout << " "; }
	}
	cout << "\n\n\n";
}

void binTree::prettyPrintTree(treeNode *curRoot) {
	queue<treeNode*>	levelNodes;
	queue<treeNode*>	nextLevelNodes;
	vector<int>		levelData;

	levelNodes.push(curRoot);

	for (int i=0; i < maxDepth(curRoot); i++) {
		while(!levelNodes.empty()) { 
			treeNode* curNode = levelNodes.front();
			levelNodes.pop();
			if (curNode == NULL) {
				levelData.push_back(0);
				nextLevelNodes.push(NULL);
				nextLevelNodes.push(NULL);
			} else {
				levelData.push_back(curNode->data);
				nextLevelNodes.push(curNode->left);
				nextLevelNodes.push(curNode->right); 
			}
		}
		printPrettyLevel(i, levelData);
		while( !nextLevelNodes.empty() ) {
			levelNodes.push(nextLevelNodes.front());
			nextLevelNodes.pop();
		}
		levelData.erase(levelData.begin(), levelData.end());
	}
	return;
	
}

treeNode* binTree::join(treeNode* a, treeNode* b) { 
	a->right = b;
	b->left = a;
}

treeNode* binTree::append(treeNode* a, treeNode* b) { 
	if (a == NULL) return b;
	if (b == NULL) return a;

	treeNode * aLast = a->left;
	treeNode * bLast = b->left;
	
	join(aLast, b);
	join(bLast, a);
	
	return a;
}

treeNode* binTree::treeToList(treeNode *curRoot) {
	if ( curRoot == NULL ) { return NULL; }
	else {
		treeNode *left = treeToList(curRoot->left);
		treeNode *right = treeToList(curRoot->right);
		
		curRoot->left = curRoot;
		curRoot->right = curRoot;
		
		left = append(left, curRoot);
		left = append(left, right);

		return left;
	}
}
		
void binTree::printLinkedList(treeNode *curRoot) {
	if (curRoot == NULL) {
		cout << "[NULL]\n";
		return;
	}

	treeNode *iterPointer = curRoot;
	while(1) {
		cout << iterPointer->data << "-->";
		iterPointer = iterPointer->right;
		if (iterPointer == curRoot) {
			cout << "[NULL]\n";
			break;
		}
	}
	return;
}
		
treeNode* binTree::invertTreeByLeaf(treeNode *curRoot, int data) {
	if (curRoot->data == data) {
		rootNode = curRoot;
		return curRoot;
	}
	
	if (data < curRoot->data) {
		if (!curRoot->left) { cout << "Can't find leaf node with data : " << data << "\n"; }
		treeNode * temp = invertTreeByLeaf(curRoot->left, data);
		if (!temp->left) {
			temp->left = curRoot;
		}
		else {
			temp->right = curRoot;
		}
		curRoot->left = NULL;
	} else {
		if (!curRoot->right) { cout << "Can't find leaf node with data : " << data << "\n"; }
		treeNode * temp = invertTreeByLeaf(curRoot->right, data);
		if (!temp->left) {
			temp->left = curRoot;
		} else {
			temp->right = curRoot;
		}
		curRoot->right = NULL;
	}
	return curRoot;
}

treeNode * binTree::createNode(int data) {
	treeNode* newNode = new treeNode;
	newNode->data = data;
	newNode->left = newNode->right = NULL;
}

treeNode * binTree::createBSTfromSortedArray(vector<int> v) {
	if (v.empty()) { return NULL; }
	if (v.size() == 1) { return createNode(*v.begin()); }

	vIntIter midNode = v.begin() + (int)(v.end() - v.begin())/2;

	treeNode* curNode = createNode(*midNode);

	vector<int> left(v.begin(), (midNode) );
	curNode->left = createBSTfromSortedArray(left);

	vector<int> right( (midNode+1), v.end() );
	curNode->right = createBSTfromSortedArray(right);

	return curNode;
}
