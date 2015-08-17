#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <queue>
#include <algorithm>

using namespace std;

typedef vector<int> 		vInt;
typedef vector<int>::iterator 	vIntIter;

class dijkastra {
	private :
		int** adj;
		int numNodes;

	public :
		dijkastra();
		void printGraph();
		void shortestPath(int);
};

dijkastra::dijkastra() {
	int _adj[9][9] = { 
				{0, -1, 15, 4, -1, -1, -1, 9, -1},
				{-1, 0, 7, -1, -1, 6, -1, -1, 11},
				{15, 7, 0, 3, -1, -1, -1, -1, -1},
				{4, -1, 3, 0, 14, -1, 6, -1, -1 },
				{-1, -1, -1, 14, 0, -1, 12, -1, 10},
				{-1, 6, -1, -1, -1, 0, -1, 7, 9},
				{-1, -1, -1, 6, 12, -1, 0, 2, -1},
				{9, -1, -1, -1, -1, 7, 2, 0, -1},
				{-1, 11, -1, -1, 10, 9, -1, -1, 0}
			 };
	numNodes = 9;

	adj = new int* [numNodes];
	for (int i=0; i < numNodes; i++) {
		adj[i] = new int[numNodes];
	}
	// Init adj
	for (int i=0; i < numNodes; i++) {
		for (int j=0; j < numNodes; j++) {
			adj[i][j] = _adj[i][j];
		}
	}
}

void dijkastra::printGraph() {
	for ( int i=0; i < numNodes; i++ ) {
		cout << "Node #" << i << " : ";
		for (int j=0; j < numNodes; j++) {
			if (adj[i][j] > 0)
				cout << j << "\t";
		}
		cout << "\n";
	}
}

typedef struct vertex {
	int id;
	bool unvisited;
	int distance;
	int parent;
} vertex;

int removeMin( vector<vertex>& Q ) {
	vector<vertex>::iterator vIter = Q.begin();
	vector<vertex>::iterator iMinValue = vIter;

	int i = 0;
	while( vIter != Q.end() ) {
		if ( (*vIter).distance < (*iMinValue).distance ) {
			iMinValue = vIter;
		}
		vIter++;
	}
	int iMin = 0;
	iMin = (*iMinValue).id;
	Q.erase(iMinValue);
	return iMin;
}

void addOrUpdate( vector<vertex>& Q, vertex& v ) {
	vector<vertex>::iterator vIter = Q.begin();
	while( vIter != Q.end() ) {
		if ( (*vIter).id == v.id ) {
			*vIter = v;
			return;
		}
		vIter++;
	}
	Q.push_back(v);
}

void dijkastra::shortestPath( int startNode ) {
	cout << "Graph : \n";
	printGraph();

	cout << "Finding shortest path to all nodes from Node #" << startNode << "\n";

	// Data Structures
	vector<vertex> nodes(numNodes);

	for (int i=0; i < numNodes; i++) {
		nodes[i].id = i;
		nodes[i].unvisited = 1;
		nodes[i].distance = 9999999;
		nodes[i].parent = -1;
	}

	nodes[startNode].distance = 0;
	
	vector<vertex> Q;

	Q.push_back(nodes[startNode]);

	cout << "Visiting Order : " << endl;
	while (!Q.empty()) {
		int u = removeMin(Q);

		nodes[u].unvisited = 0;
		cout << u << " ";

		// Go over all edges of U and update their weights
		for ( int i=0; i < numNodes; i++ ) {
			if (adj[u][i] > 0 && nodes[i].unvisited) {
				if (nodes[i].distance > nodes[u].distance + adj[u][i]) {
					nodes[i].parent = u;
					nodes[i].distance = nodes[u].distance + adj[u][i];
					addOrUpdate(Q, nodes[i]);
				}	
			}
		}
	}

	cout << "\nDistance from Node " << startNode << " : \n";
	for ( int i=0; i < numNodes; i++ ) {
		cout << "Node " << i << " : " << nodes[i].distance << "\n";
		int j = i; 
		while (j!=startNode) {
			cout << nodes[j].parent << "-->";
			j = nodes[j].parent;
		}
		cout << "\n";
	}
}

int main (int argc, char *argv[]) {
	dijkastra d;
	d.shortestPath(0);	
	return 0;
}
