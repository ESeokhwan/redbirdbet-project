#include "matrix.h"

int main(){
	int row, col;
	cin >> row >> col;
	matrix mat(row,col);

	mat.fill();

	cout << endl;
	mat.show();

	mat = mat.RREF();
	
	cout << endl;
	mat.show();
	mat.show(1);

	return 0;
}
