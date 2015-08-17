#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <stack>

using namespace std;

#define ROW_HEIGHT 400
#define COL_WIDTH 600

typedef vector<int> 		vInt;
typedef vector<int>::iterator 	vIntIter;

class node {
	private:
		int x;
		int y;
	public:
		node (int _x, int _y) { x = _x; y = _y; };
		int getX() { return x; };
		int getY() { return y; };
};

class grafixMask {
	private :
		bool fillArea[ROW_HEIGHT][COL_WIDTH];
		
	public :
		grafixMask();
		int* sortedAreas( string * );
		void fillRect( int, int, int, int, int );
		void getRectangle(string, int&, int&, int&, int&);
		void printFillArea();
		int doFill(int x, int y);
};

grafixMask::grafixMask() {
	// UnFill the Slate 
	fillRect(0, 0, ROW_HEIGHT-1, COL_WIDTH-1, 0);
}

void grafixMask::fillRect ( int x1, int y1, int x2, int y2, int value ) {
	for (int i = x1; i <= x2; i++ ) {
		for ( int j = y1; j <= y2; j++ ) {
			fillArea[i][j] = value;
		}
	}
}

void grafixMask::printFillArea() {
	for (int i = 0; i < ROW_HEIGHT; i++ ) {
		for ( int j = 0; j < COL_WIDTH; j++ ) {
			if (j%10==0) cout << " ";
			if (fillArea[i][j]) cout << "x";
			else cout << ".";
		}
		cout << "\n";
	}
	cout << "\n";
}

void grafixMask::getRectangle(string curRect, int& x1, int& y1, int& x2, int& y2) {
	int j = 0;
	string x1S="", y1S="", x2S="", y2S=""; 
	while ( j < curRect.length() ) {
		while (  curRect[j] != ' ' ) {
			x1S += curRect[j];
			j++;
		}
		j++; 
		while (  curRect[j] != ' ' ) {
			y1S += curRect[j];
			j++;
		}
		j++; 
		while (  curRect[j] != ' ' ) {
			x2S += curRect[j];
			j++;
		}
		j++; 
		while (  curRect[j] != '\0' ) {
			y2S += curRect[j];
			j++;
		}
	}

	// Set return values by ref
	x1 = atoi(x1S.c_str());
	y1 = atoi(y1S.c_str());
	x2 = atoi(x2S.c_str());
	y2 = atoi(y2S.c_str()); 
}

int grafixMask::doFill(int x, int y) {
	stack<node> dfs; 
	dfs.push(node(x, y));
	
	int countArea = 0;
	while ( !dfs.empty() ) {
		node curNode = dfs.top();
		x = curNode.getX();
		y = curNode.getY();
		dfs.pop();

		if (x < 0 || x >= ROW_HEIGHT || y < 0 || y >= COL_WIDTH) continue;
		if (fillArea[x][y]) continue;
			
		fillArea[x][y] = 1;
		countArea++;

		dfs.push(node(x-1,y));
		dfs.push(node(x+1,y));
		dfs.push(node(x,y-1));
		dfs.push(node(x,y+1));
	}
	return countArea;
}

int* grafixMask::sortedAreas( string* rectangles ) {
	// Init Area
	//cout << "Init Fill Area : \n";
	//printFillArea();
	
	// Fill the input rects
	int i = 0; 
	int x1, y1, x2, y2;
	
	//while ( rectangles[i].length() ) {
	while ( i < 50 ) {
		string curRect = rectangles[i];
		getRectangle(curRect, x1, y1, x2, y2); 	
		cout << "Rectangle : " << x1 << " " << y1 << " " << x2 << " " << y2 << "\n";
		fillRect (x1, y1, x2, y2, 1);
		i++;
	}

	//cout << "Fill Area w/ Rectangles : \n";
	//printFillArea();

	vector<int> sortedAreas;
	for (int i = 0; i < ROW_HEIGHT; i++) { 
		for (int j = 0; j < COL_WIDTH; j++) {
			if (!fillArea[i][j]) {
				int newArea = doFill(i, j);
				cout << "Found area : " << newArea << "\n";
				sortedAreas.push_back(newArea);
			}
		}
	}
	cout << "Done finding areas\n";
	sort(sortedAreas.begin(), sortedAreas.end());

	cout << "Found Areas in sorted order : ";
	for (vIntIter iter = sortedAreas.begin(); iter != sortedAreas.end(); iter++ ) {
		cout << "\t" << *iter;
	}
	cout << "\n";
	
	int *a = new int[sortedAreas.size()];
	i = 0;
	while ( i < sortedAreas.size()) {
		a[i] = sortedAreas[i];
		i++;
	}
	
	return a;
}

int main (int argc, char *argv[]) {
	//string rectangles[] = {"0 292 399 307"};
	//string rectangles[] = {"48 192 351 207", "48 392 351 407", "120 52 135 547", "260 52 275 547"};
	//string rectangles[] = {"0 192 399 207", "0 392 399 407", "120 0 135 599", "260 0 275 599"};
	//string rectangles[] = {"50 300 199 300", "201 300 350 300", "200 50 200 299", "200 301 200 550"};

	string rectangles[] = {"0 20 399 20", "0 44 399 44", "0 68 399 68", "0 92 399 92",
		"0 116 399 116", "0 140 399 140", "0 164 399 164", "0 188 399 188",
		"0 212 399 212", "0 236 399 236", "0 260 399 260", "0 284 399 284",
		"0 308 399 308", "0 332 399 332", "0 356 399 356", "0 380 399 380",
		"0 404 399 404", "0 428 399 428", "0 452 399 452", "0 476 399 476",
		"0 500 399 500", "0 524 399 524", "0 548 399 548", "0 572 399 572",
		"0 596 399 596", "5 0 5 599", "21 0 21 599", "37 0 37 599",
		"53 0 53 599", "69 0 69 599", "85 0 85 599", "101 0 101 599",
		"117 0 117 599", "133 0 133 599", "149 0 149 599", "165 0 165 599",
		"181 0 181 599", "197 0 197 599", "213 0 213 599", "229 0 229 599",
		"245 0 245 599", "261 0 261 599", "277 0 277 599", "293 0 293 599",
		"309 0 309 599", "325 0 325 599", "341 0 341 599", "357 0 357 599",
		"373 0 373 599", "389 0 389 599"};

	grafixMask gfx;
	int *areas = gfx.sortedAreas(rectangles);

	//cout << "\nFounded areas : \n";
	//while (*areas) { cout << "\t" << *areas << "\n"; areas++; }
	
	return 0;
}
