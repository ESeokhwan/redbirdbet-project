#include "matrix.h"

int main(){
	int row,col;
	cin >> row >> col;
	matrix mat(row,col);
	mat.fill();

	cout << endl;
	mat.show();
	mat.show_double();
	mat.find_determinant();
	fraction determinant = mat.get_determinant();
//	mat.eliminate().show();
	cout << "determinant of matrix : " << determinant << endl;
	cout << "in form of double : " << determinant.getValue() << endl;

	return 0;
}
