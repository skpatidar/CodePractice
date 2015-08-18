/**
 * Binary Trees
    * BuildBST, Insert, Remove, Find
    * Print Pre/Post/In Order
    * Print level order / pretty Print Tree
    * Print all paths in the tree 
    * Tree to Doubly Linked List - Recursion
    * Left view of a tree [Level order traversal]
 
 * Linked List Class - Frequent Operations
    * Reverse / getNth / insertNth / deleteList 
    * sortlist (mergeSort) / frontBackSplit / alternateSplit 
 
 * Sorting Algos
    * Quick Sort v/s Merge Sort
    
**/

#include<iostream>
#include<vector>
#include<stdlib.h>
#include<iomanip>
#include<deque>
#include<math.h>

using namespace std;
typedef vector<int> vI;
typedef vector<int>::iterator vIter;

void printArray(vector<int> A) {
    for (vector<int>::iterator iter=A.begin(); iter != A.end(); ) {
        cout << *iter;
        iter++;
        if (iter != A.end()) 
            cout << ", ";
        else 
            cout << "\n";
    }
}

void generateRandomArray(vector<int> &A, int n) {
    A.clear();
    for (int i=0; i < n; i++) {
        A.push_back(rand()%1024);
    }
}

void swap(vector<int> &A, int i, int j) {
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

void quickSort(vector<int> &A, int lo, int hi) {
    if (hi < lo) return;
    
    int pivot = lo, swapIndex = lo+1;
    for (int i=lo+1; i <= hi; i++) {
        if (A[i] < A[pivot]) {
            swap(A, i, swapIndex);
            swapIndex++;
        }
    }
    swap(A, pivot, swapIndex-1);
    quickSort(A, lo, swapIndex - 2);
    quickSort(A, swapIndex, hi);
}

void qSort(vector<int> &A) {
    quickSort(A, 0, (A.size()-1));
}

vector<int> mergeSortedArrays(vector<int> A, vector<int> B) {
    vI sorted;
    vIter one, two;
    for (one = A.begin(), two = B.begin(); one != A.end() && two != B.end(); ){
        if (*one < *two) {
            sorted.push_back(*one);
            one++;
        } else {
            sorted.push_back(*two);
            two++;
        }
    }
    while(one != A.end()) {
        sorted.push_back(*one);
        one++;
    }
    while(two != B.end()) {
        sorted.push_back(*two);
        two++;
    }
    return sorted;
}

vector<int> mergeSort(vector<int> A, int low, int high) {
    if (high <= low) {
        vector<int> retArray;
        if (low == high) { 
            retArray.push_back(A[low]);
        } 
        return retArray; 
    }
    
    int mid = (high + low)/2 + 1;
    
    vector<int> one = mergeSort(A, low, mid-1);
    vector<int> two = mergeSort(A, mid, high);
    vector<int> sorted = mergeSortedArrays(one, two);
    return sorted;
}

struct treeNode {
    int data;
    treeNode *left;
    treeNode *right;
};
typedef struct treeNode treeNode; 

struct linkNode {
    int data;
    linkNode *next;    
};
typedef struct linkNode linkNode;

treeNode* buildBST(const vector<int> &A, int lo, int hi) {
    if (hi < lo) return NULL;
    treeNode *rootNode = new treeNode;
    int rootIndex = lo + (hi - lo)/2;
    rootNode->data = A[rootIndex];
    rootNode->left = buildBST(A, lo, rootIndex-1);
    rootNode->right = buildBST(A, rootIndex+1, hi);    
    return rootNode;
}

void printTreeInOrder(treeNode *rootNode) {
    if (rootNode==NULL) return;
    printTreeInOrder(rootNode->left);
    cout << "*" << rootNode->data << "*";
    printTreeInOrder(rootNode->right);
}

void printTreePreOrder(treeNode *rootNode) {
    if (rootNode==NULL) return;
    cout << "*" << rootNode->data << "*";
    printTreePreOrder(rootNode->left);
    printTreePreOrder(rootNode->right);
}

void printTreePostOrder(treeNode *rootNode) {
    if (rootNode==NULL) return;
    printTreePostOrder(rootNode->left);
    printTreePostOrder(rootNode->right);
    cout << "*" << rootNode->data << "*";
}

void drawChildLines(int level) {
    int incIndent = 100 / (int) pow(2.0, (float)(level-1));
    int initIndent = incIndent / 2 ; 
    
    int numElements = pow(2.0, (float)(level-1));
    
    bool firstElementDone = false;
    for (int i=0; i < numElements; i++) {
        if (firstElementDone) {
            cout << std::setw(incIndent) << "^";    
        } else {
            cout << std::setw(initIndent) << "^";
            firstElementDone = true;
        }
    }
    cout << "\n";
}

int processQueue(deque<treeNode*> &use, deque<treeNode*> &fill, int level) {
    int incIndent = 100 / (int) pow(2.0, (float)(level-1));
    int initIndent = incIndent / 2 ;
    
    bool firstElementDone = false;
    int elementsFilled = 0;
    while(!use.empty()) {
        treeNode* current = use.front();
        
        if (current != NULL) { 
            if (!firstElementDone) { 
                cout << std::setw(initIndent) << current->data << " ";
                firstElementDone = true;
            } else {
                cout << std::setw(incIndent) << current->data << " ";
            }
        } else {
            if (!firstElementDone) { 
                cout << std::setw(initIndent) << "X";
                firstElementDone = true;
            } else {
                cout << std::setw(incIndent) << "X";
            }
            fill.push_back(NULL);
            fill.push_back(NULL);
            use.pop_front();
            continue;
        }
        if(current->left != NULL) {
            fill.push_back(current->left);
            elementsFilled++;
        } else {
            fill.push_back(NULL);
        }
        if(current->right != NULL) {
            fill.push_back(current->right);
            elementsFilled++;
        } else {
            fill.push_back(NULL);
        }
        use.pop_front();
    }
    cout << "\n\n";
    return elementsFilled;
}

void printLevelOrderTree(treeNode *root) {
    if (root == NULL) return;
    
    deque<treeNode*> first;
    deque<treeNode*> second;
    
    first.push_back(root);
    
    int level=1, elementsFilled = 1;
    while(elementsFilled > 0) {
        if (first.size() > 0)
            elementsFilled = processQueue(first, second, level);
        else 
            elementsFilled = processQueue(second, first, level);
        level++;
    }
}

void addNode(treeNode* root, treeNode* d, bool isRight) {
    if (isRight) root->right = d;
    else root->left = d;
}

void insert(treeNode* root, treeNode *d) {
    if (root == NULL) return;
    if (root->data == d->data) return; 
    
    if (root->data > d->data) {
        if (root->left == NULL) {
            addNode(root, d, 0); 
        } else {
            insert(root->left, d);
        }
    } else {
        if (root->right == NULL) {
            addNode(root, d, 1);
        } else {
            insert(root->right, d);
        }
    }
}

// Returns (new) root node to the tree 
treeNode* remove(treeNode *root, int d) {
    if (root == NULL) return NULL;
    if (root->data == d) {  // This node has the matching data
        insert(root->right, root->left);
        return root->right;
    }
    
    if (root->data > d) root->left = remove(root->left, d);
    else root->right = remove(root->right, d);
    
    return root;
}

treeNode* addNode(treeNode* root, int d, bool isRight) {
    treeNode * newleaf = new treeNode;
    newleaf->data = d;
    newleaf->left = newleaf->right = NULL;
    if (isRight) root->right = newleaf;
    else root->left = newleaf;
    return newleaf;
}

treeNode* insert(treeNode* root, int d) {
    if (root == NULL) return NULL;
    if (root->data == d) return NULL; 
    
    if (root->data > d) {
        if (root->left == NULL) {
            return addNode(root, d, 0); 
        } else {
            return insert(root->left, d);
        }
    } else {
        if (root->right == NULL) {
            return addNode(root, d, 1);
        } else {
            return insert(root->right, d);
        }
    }
}

treeNode* find(treeNode *root, int d) {
    if (root == NULL) return NULL;
    
    if (root->data == d) return root; 
    
    if (root->data < d) return find(root->right, d);
    else return find(root->left, d);
}

void rTree(treeNode *root, treeNode *parent, int d) {
    if (root==NULL) return;
    if (d < root->data) {
        rTree(root->left, root, d);
        root->left = parent;
    } else if (d > root->data) {
        rTree(root->right, root, d);
        root->right = parent;
    } else {
        root->left = parent;
    }
    return;   
}

treeNode* reverseHangTree(treeNode *root, int d) {
    treeNode* newRoot = find(root, d);
    if (newRoot != NULL) { 
        rTree(root, NULL, d);
        return newRoot;
    } else {
        cout << "Not found leaf with data : " << d << "\n";
    }
}

void binTreePrintPaths(treeNode* root, vector<int> pathData) {
    pathData.push_back(root->data);
    if (root->left == NULL && root->right == NULL) {
        printArray(pathData);
        return;
    } 
    if (root->left != NULL) binTreePrintPaths(root->left, pathData);
    if (root->right != NULL) binTreePrintPaths(root->right, pathData);
}

void printAllPaths(treeNode* root) {
    if (root == NULL) return;
    vector<int> pathData;
    binTreePrintPaths(root, pathData);
}

treeNode* findPre(treeNode *root) {
    treeNode *temp = root;
    while(temp->right != NULL) {
        temp = temp->right;
    } 
    return temp; 
}

treeNode* findPost(treeNode *root) {
    treeNode *temp = root;
    while(temp->left != NULL) {
        temp = temp->left;
    } 
    return temp; 
}

void convertBinTreeToDLL(treeNode * root) {
    if (root->left != NULL) {
        convertBinTreeToDLL(root->left);
        root->left = findPre(root->left);
        root->left->right = root;
    } 
    if (root->right != NULL) {
        convertBinTreeToDLL(root->right);
        root->right = findPost(root->right);
        root->right->left = root;
    }
}

treeNode* convertToDLL(treeNode *root) {
    if (NULL == root) return NULL;
    convertBinTreeToDLL(root);
    while (root->left != NULL) root = root->left;
    return root;
}

void printDLL(treeNode* head) {
    if (NULL == head) return;
    treeNode *walk = head;
    while(walk != NULL) {
        cout << walk->data << "<-->";
        walk = walk->right;
    }
    cout << "NULL\n";
}

void printLinkList(linkNode* head) {
    cout << "List : ";
    linkNode *node = head;
    while(node != NULL) {
        cout << node->data << "-->";
        node = node->next;
    }
    cout << "NULL\n";
}

void rLinkList(linkNode* head) {
    if (head == NULL) return;
    if (head->next != NULL) {
        rLinkList(head->next);
        head->next->next = head; 
        head->next = NULL;
    }
}

linkNode* getLastNode(linkNode* head) {
    linkNode* temp = head;
    while(temp->next != NULL) {
        temp = temp->next;
    } 
    return temp;
}

linkNode* reverseLinkList(linkNode* head) {
    if (head==NULL) return NULL;
    linkNode* newHead = getLastNode(head);
    rLinkList(head); 
    return newHead;
}

linkNode* buildLinkList(vector<int> A) {
    cout <<"Building link list from : ";
    printArray(A);
    
    linkNode* head = NULL;
    linkNode* curNode = head;
    for (vector<int>::iterator iter = A.begin(); iter != A.end(); iter++) {
        linkNode* newNode = new linkNode;
        newNode->data = *iter;
        newNode->next = NULL;
        
        if (curNode != NULL) curNode->next = newNode; 
        curNode = newNode; 
        if (head == NULL) head = curNode; 
    }
    printLinkList(head);
    return head;
}

int getNth(linkNode* head, int pos) {
    linkNode* node = head;
    int _pos = 0;
    while (_pos != pos && node != NULL) {
        node = node->next;
        _pos++;
    }
    if (node == NULL) {
        cout << "Location : " << pos << " does not exist \n";
        return -1;
    }
    return node->data; 
}

linkNode* insertNth(linkNode* head, int pos, int data) {
    if (pos==0) { // handle case where head changes
        linkNode * newHead = new linkNode;
        newHead->data = data;
        newHead->next = head; 
        return newHead; 
    }
    
    int _pos = 1; 
    linkNode* insertLoc = head; 
    while(_pos != pos && insertLoc != NULL) {
        insertLoc = insertLoc->next; 
        _pos++;
    }
    
    if (insertLoc == NULL) {
        cout << "Insert location higher than total # of elements\n";
        return head;
    }
    
    linkNode *newNode = new linkNode;
    newNode->next = insertLoc->next;
    newNode->data = data;
    insertLoc->next = newNode;
    
    return head;
}

void deleteList(linkNode* head) {
    if (head == NULL) return;
    if (head->next != NULL) deleteList(head->next);
    cout << "\tDeleting : " << head->data;
    delete head;
    return;
}

void frontBackSplit(linkNode* head, linkNode* &front, linkNode* &back) {
    if (NULL == head) {
        front = back = head;
        return;
    }
    
    front = head;
    back = head->next;
    while (back != NULL) {
        if(back->next != NULL) {
            front = front->next;
            back = back->next->next;
        } else {
            back = back->next;
        }
    }
    back = front->next;
    front->next = NULL;
    front = head;
}

void oddEvenSplit(linkNode* head, linkNode* &odd, linkNode* &even) {
    if (head == NULL) {
        odd = even = head;
        return;
    }
    
    // Init odd/even 
    odd = head;
    even = head->next;
    
    // Last node for odd / even lists
    linkNode* oddTail = odd;
    linkNode* evenTail = even;
    
    // Next pair of odd/even to be connected to the list
    linkNode* nextPair = NULL;
    
    if (even == NULL) {
        return;
    }
    
    nextPair = even->next;
    oddTail->next = NULL;
    evenTail->next = NULL;
    
    while(nextPair != NULL) {
        oddTail->next = nextPair;
        evenTail->next = nextPair->next;
        oddTail = oddTail->next;
        evenTail = evenTail->next;
        
        //update nextPair 
        nextPair = nextPair->next;
        if (nextPair != NULL) nextPair = nextPair->next;
        
        // now update odd/even last nodes to point to NULL 
        oddTail->next = NULL;
        if (evenTail != NULL) {
            evenTail->next = NULL; 
        }
    }
}

void mergeSortedLists(linkNode* &head, linkNode* l1, linkNode* l2) {
    if (l1 == NULL) {
        head = l2; 
        return;
    } 
    if (l2 == NULL) {
        head = l1;
    }
    
    if (l1->data < l2->data) {
        head = l1;
        l1 = l1->next;
    } else {
        head = l2;
        l2 = l2->next;
    }
    linkNode* currNode = head;
    while(l1 != NULL && l2 != NULL) {
        if (l1->data < l2->data) {
            currNode->next = l1; 
            l1 = l1->next;
        } else {
            currNode->next = l2;
            l2 = l2->next;
        }
        currNode = currNode->next;
    }
    
    if (l1 != NULL) {
        currNode->next = l1;
    } else if (l2 != NULL) {
        currNode->next = l2;
    }
    
}

linkNode* mergeSortLists(linkNode* list) {
    // Base case 
    if (list == NULL) return list;
    if (list->next == NULL) return list;
    
    // Break the list 
    linkNode *front, *back;
    frontBackSplit(list, front, back);
    
    // Merge Sort recursive 
    front = mergeSortLists(front);
    back = mergeSortLists(back);
    
    // Merge sorted lists
    mergeSortedLists(list, front, back);
    
    return list;
}

int main() {
    int n; 
    cout << "Enter # of elements in the array : ";
    cin >> n;
    
    vector<int> A;
    
    cout << "Initial array : "; generateRandomArray(A, n); printArray(A);
    //qSort(A); cout << "Sorted array : "; printArray(A);
    vector<int> B = mergeSort(A, 0, A.size()-1); cout << "Sorted array : "; printArray(B);
    
    //linkNode *list1 = buildLinkList(A);
    
    //cout << "Initial array : "; generateRandomArray(A, n+1); printArray(A);
    //qSort(A); cout << "Sorted array : "; printArray(A);
    //linkNode *list2 = buildLinkList(A);

    /*
    linkNode *sortedList; 
    sortedList = mergeSortLists(list1);
    cout << "[Sorted]"; printLinkList(sortedList);
    */
    
    /*
    mergeSortedLists(sortedList, list1, list2); 
    cout << "Merged sorted list : "; printLinkList(sortedList);
    */

/* 
    treeNode *root = buildBST(A, 0, A.size()-1);
    cout << "\nPrint tree pre-order\n"; printTreePreOrder(root);
    cout << "\nPrint tree in-order\n"; printTreeInOrder(root);
    cout << "\nPrint tree post-order\n"; printTreePostOrder(root);

    cout <<"\nPrint level order tree : \n"; printLevelOrderTree(root);
    
    treeNode *dllHead = convertToDLL(root);
    cout << "\nPrint DLL from Tree \n"; printDLL(dllHead);
    
    treeNode* temp;
    temp = insert(root, 212);
    cout <<"\nInsert 212 : \n"; printLevelOrderTree(root);
    
    temp = insert(root, 199);
    cout <<"\nInsert 199 : \n"; printLevelOrderTree(root);
    
    temp = insert(root, 333);
    cout <<"\nInsert 333 : \n"; printLevelOrderTree(root);
    
    temp = insert(root, 444);
    cout <<"\nInsert 444 : \n"; printLevelOrderTree(root);
    
    temp = insert(root, 512);
    cout <<"\nInsert 512 : \n"; printLevelOrderTree(root);
    
    root = remove(root, 212);
    cout <<"\nRemove 212 : \n"; printLevelOrderTree(root);
     
    root = remove(root, 333);
    cout <<"\nRemove 333 : \n"; printLevelOrderTree(root);
    
    root = remove(root, 199);
    cout <<"\nRemove 199 : \n"; printLevelOrderTree(root);
    
    cout <<"\nPrint tree paths : \n"; printAllPaths(root);

    root = reverseHangTree(root, 512); 
    cout <<"\nReversed tree by leafNode : 512 : \n"; printLevelOrderTree(root);
*/

 
/* 
    head = reverseLinkList(head);
    cout << "Reversed Link List : "; printLinkList(head);
    
    head = insertNth(head, 0, 99);
    cout << "Insert 99 @ 0 : "; printLinkList(head);
    
    head = insertNth(head, 2, 22);
    cout << "Insert 22 @ 2 : "; printLinkList(head);
    cout << "Get @ 2 : " << getNth(head, 2) << "\n";
    
    linkNode *front, *back;
    //frontBackSplit(head, front, back);
    oddEvenSplit(head, front, back);
    cout << "\nFront List : "; printLinkList(front);
    cout << "\nBack List : "; printLinkList(back);
    cout << "\nDelete List : "; deleteList(front);
    cout << "\nDelete List : "; deleteList(back);    
*/    
   
    
}
