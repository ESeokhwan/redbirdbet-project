#include "matrix.h"

int main(){
	int row, col;
	cin >> row >> col;

	matrix mat(row,col);
	mat.fill();

	cout << "matrix input" << endl;
	mat.show();

	matrix mat_t = mat.transpose();

	cout << "C(A)" << endl;
	matrix col_space = mat.column_space();
	col_space.show();

	cout << "N(A)" << endl;
	matrix null_space = mat.null_space();
	null_space.show();

	cout << "C(At)" << endl;
	matrix tcol_space = mat_t.column_space();
	tcol_space.show();

	cout << "N(At)" << endl;
	matrix tnull_space = mat_t.null_space();
	tnull_space.show();

	cout << "check C(A) * N(At)" << endl;
	matrix temp =  tnull_space.transpose() * col_space;
	temp.show();

	cout << "check C(At) * N(A)" << endl;
	temp = tcol_space.transpose() * null_space;
	temp.show();

	return 0;
}

