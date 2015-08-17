#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

#define MAX_DATA 1024

typedef struct trieNode {
	int value;
	char key;
	struct trieNode* next;
	struct trieNode* children;

};

