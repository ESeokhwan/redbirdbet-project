#include "matrix.h"

int main() {
	int len;
	cin >> len;

	matrix b(len, 1);
	b.fill();

	int row, col;
	cin >> row >> col;

	matrix mat(row,col);
	mat.fill();
	cout << endl;
	
	cout << "vector input" << endl;
	b.show();
	cout << endl;

	cout << "matrix input" << endl;
	mat.show();
	cout << endl;

	cout << "projection matrix" << endl;
	mat.projection_matrix().show();

	cout << "projection" << endl;
	b.project(mat).show();

	return 0;
}
