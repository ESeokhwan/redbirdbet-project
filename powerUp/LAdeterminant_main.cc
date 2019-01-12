#include "matrix.h"

int main(){
	int row,col;
	cin >> row >> col;
	matrix mat(row,col);
	mat.fill();

	cout << endl;
	mat.show();
	mat.find_determinant();
	fraction determinant = mat.get_determinant();

	cout << "determinant of matrix : " << determinant << endl;

	return 0;
}
