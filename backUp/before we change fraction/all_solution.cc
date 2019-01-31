#include "matrix.h"

int main(){
	int col, row;
	cin >> row >> col;
	matrix A(row, col);
	A.fill();
	cout << "input b" << endl;
	matrix b(row,1);
	b.fill();

	cout << "A :" << endl;
	A.show();

	cout << "b :" << endl;
	b.show();

	matrix particular = A.all_solution(b);
	
	cout << "x_particular : " << endl;
	particular.show();

	cout << "x_null : " << endl;
	matrix null = A.null_space();
	null.show();

	return 0;
}
