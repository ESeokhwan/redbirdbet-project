#include "matrix.h"

int main(){
	int row, col;
	cin >> row >> col;

	matrix mat(row,col);
	mat.fill();
	
	cout << "matrix input" << endl;
	mat.show();

	matrix elim = mat.eliminate();

	cout << "elim" << endl;
	elim.show();

	matrix rref = mat.RREF();

	cout << "RREF" << endl;
	rref.show();

	matrix temp = mat.all_solution();

	cout << "N(matrix)" << endl;
	temp.show();

	temp = mat * temp;

	cout << "matrix * null_space of matrix" <<endl;
	temp.show();

	return 0;
}


	
