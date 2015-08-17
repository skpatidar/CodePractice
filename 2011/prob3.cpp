#include <iostream>
using namespace std;

const int MAX_SIZE = 20;
typedef int ARR2D[MAX_SIZE][MAX_SIZE];

void Print(ARR2D in_array, int rows, int cols);
void Fill(ARR2D in_array, int rows, int cols);

int main() {
  ARR2D matrix;
  int row, col;
  do {
    cout << "Please enter the size of the matrix to generate (rows and cols) :" << endl;
    cin >> row >> col;
  } while (row <= 0 || row > MAX_SIZE || col <= 0 || col > MAX_SIZE);
  Fill(matrix, row, col);
  Print(matrix, row, col);
  return(0);
}

void Print(ARR2D in_array, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++)
      cout << '\t' << in_array[i][j];
    cout << endl;
  }
}

void Fill(ARR2D in_array, int rows, int cols) {

  for(int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
      in_array[i][j] = 0;

  const int limit = rows * cols;
  int cNum = 1;
  int cRow = 0;
  int cCol = 0;
  int cDir = 0;  // 0-north, 1-east, 2-south, 3-west

  while(true) {
    // Place the number.
    in_array[cRow][cCol] = cNum;
    cNum++;
    if (cNum > limit) break;

    int fRow = cRow;
    int fCol = cCol;
    while (true) {
      fRow = cRow;
      fCol = cCol;
      switch(cDir) {
        case 0: fRow--; break;
        case 1: fCol++; break;
        case 2: fRow++; break;
        case 3: fCol--; break;
      }

      if ( fRow >= 0 && fRow < rows && fCol >= 0 && fCol < cols && in_array[fRow][fCol] == 0)
        break;
      cDir = (cDir + 1) % 4;
    }
    cRow = fRow;
    cCol = fCol;
  }
}
