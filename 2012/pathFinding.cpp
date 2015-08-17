#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <queue>

using namespace std;

typedef vector<int> 		vInt;
typedef vector<int>::iterator 	vIntIter;

class node {

	public:
		int p1x, p1y, p2x, p2y;
		int numTurns;
		node (int _p1x, int _p1y, int _p2x, int _p2y, int _nT) { p1x = _p1x; p1y = _p1y; p2x = _p2x; p2y = _p2y; numTurns = _nT; };
};

class pathFinding {
	private :
		bool visited[20][20][20][20];
		char board[20][20];
		int boardX, boardY;
		int p1x, p1y, p2x, p2y;
		
	public :
		pathFinding(){};
		int minTurns(string *, int , int);
		void printBoard();
		void initBoard(string *, int , int);
};

void pathFinding::initBoard ( string * b, int _bx, int _by) {
	boardX = _bx;
	boardY = _by;

	cout << "Board X : " << boardX << " Board Y : " << boardY << "\n";

	for (int i = 0; i < boardX; i++) {
		string curRow = b[i];
		cout << "Current String : " << curRow << "\n";
		for (int j = 0; j < boardY; j++) {
			board[i][j] = curRow[j];
			if (curRow[j] == 'A') { p1x = i; p1y = j; cout << "Player A is at : (" << i << ", " << j << "\n";}
			if (curRow[j] == 'B') { p2x = i; p2y = j; cout << "Player B is at : (" << i << ", " << j << "\n";}
		}
	}
}

void pathFinding::printBoard() {
	for (int i = 0; i < boardX; i++ ) {
		for ( int j = 0; j < boardY; j++ ) {
			cout << board[i][j];
		}
		cout << "\n";
	}
	cout << "\n";
}

int pathFinding::minTurns( string b[], int _bx, int _by ) {
	initBoard(b, _bx, _by);

	// Init Area
	cout << "Board State at Init : \n";
	printBoard();

	node start(p1x, p1y, p2x, p2y, 0);
	
	queue<node> bfs;
	bfs.push(start);

	while (!bfs.empty()) {
		node top = bfs.front();
		bfs.pop();

		//cout << "Node Info : \n"; 
		//cout << "\tPlayer A : " << top.p1x << ", " << top.p1y << "\n";
		//cout << "\tPlayer B : " << top.p2x << ", " << top.p2y << "\n";

		// Check for Player X, Y out of bounds  or hitting the wall
		if ( (top.p1x < 0) || (top.p1x >= boardX) || (top.p1y < 0) || (top.p1y >= boardY) ) continue;
		if ( (top.p2x < 0) || (top.p2x >= boardX) || (top.p2y < 0) || (top.p2y >= boardY) ) continue;
		if ( board[top.p1x][top.p1y] == 'X' ) continue;
		if ( board[top.p2x][top.p2y] == 'X' ) continue;

		// Check for Player X, Y not to be on same node
		if ( top.p1x == top.p2x && top.p1y == top.p2y ) continue;

		// Check if Visited already 
		if ( visited[top.p1x][top.p1y][top.p2x][top.p2y] ) continue;

		// Mark Visited
		visited[top.p1x][top.p1y][top.p2x][top.p2y] = 1;

		// Check if we have swapped the position of A and B and can return 
		if ( top.p1x == start.p2x && top.p1y == start.p2y && top.p2x == start.p1x && top.p2y == start.p1y ) return top.numTurns; 

		// Add all possible moves for A and B - making sure they don't switch with each other 
		for (int player1XDelta = -1; player1XDelta <= 1; player1XDelta++) {
			for (int player1YDelta = -1; player1YDelta <= 1; player1YDelta++) {
				for (int player2XDelta = -1; player2XDelta <= 1; player2XDelta++) {
					for (int player2YDelta = -1; player2YDelta <= 1; player2YDelta++) {
						// Check that you don't swap A and B's positions in one go
						if ( top.p1x == top.p2x + player2XDelta && top.p1y == top.p2y + player2YDelta 
						 && top.p2x == top.p1x + player1XDelta && top.p2y == top.p1y + player1YDelta )
						{ continue; }
						//cout << "Adding new node : " << top.p1x + player1XDelta << ", " << top.p1y + player1YDelta << ", " << top.p2x + player2XDelta << ", " << top.p2y + player2YDelta << "\n";
						// Add the new node into the queue
						bfs.push(node(top.p1x + player1XDelta, top.p1y + player1YDelta,	
							      top.p2x + player2XDelta, top.p2y + player2YDelta, 
							      top.numTurns + 1));
					}
				}
			}
		}
	}
	return -1;
}

int main (int argc, char *argv[]) {
/*	string b[] = { "....", ".A..", "..B.", "...." };

	string b[] = {"XXXXXXXXX", "A...X...B", "XXXXXXXXX"};

	string b[] = {"XXXXXXXXX", "A.......B", "XXXXXXXXX"};

	string b[] = {"XXXXXXXXX", "A.......B", "XXXX.XXXX"};

	string b[] = {"...A.XXXXX.....", ".....XXXXX.....", "...............", ".....XXXXX.B...", ".....XXXXX....."};
*/

	string b[] = {"AB.................X", "XXXXXXXXXXXXXXXXXXX.", "X..................X",  ".XXXXXXXXXXXXXXXXXXX", "X..................X",
		     "XXXXXXXXXXXXXXXXXXX.", "X..................X", ".XXXXXXXXXXXXXXXXXXX", "X..................X", "XXXXXXXXXXXXXXXXXXX.",
		     "X..................X", ".XXXXXXXXXXXXXXXXXXX", "X..................X", "XXXXXXXXXXXXXXXXXXX.", "X..................X",
		     ".XXXXXXXXXXXXXXXXXXX", "X..................X", "XXXXXXXXXXXXXXXXXXX.", "...................X", ".XXXXXXXXXXXXXXXXXXX"};
/*
*/
	pathFinding p;
	int turns = p.minTurns(b, 20, 20);
	cout << "\nTurns : " << turns << " \n";
	
	return 0;
}
