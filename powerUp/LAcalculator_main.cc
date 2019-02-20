#include "matrix.h"

int main() {
	int row , col;
	cin >> row >> col;
	matrix mat1(row,col);
	mat1.fill();

	cin >> row >> col;
	matrix mat2(row,col);
	mat2.fill();

	mat1.show();

	cout << endl;

	mat2.show();

	matrix matadd = mat1 + mat2;

	matrix matsub = mat1 - mat2;

	matrix matmul = mat1 * mat2;

	cout << endl;
	matadd.show();

	cout << endl;
	matsub.show();

	cout << endl;
	matmul.show();

	return 0;
}
