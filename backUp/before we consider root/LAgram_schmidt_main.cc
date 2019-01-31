#include "matrix.h"

int main(){
	int col, row;
	cin >> row >> col;
	matrix mat(row, col);
	mat.fill();
	
	cout << endl;
	mat.show();

	cout << endl;
	mat.gram_schmidt().show();

	return 0;
}
