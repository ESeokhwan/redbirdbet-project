#include "matrix.h"

int main(){
	int r, c, i, j;
	cin >> r >> c;

	matrix mat(r,c);

	mat.fill();
	
	mat.show();

	cout << endl;

	matrix eigenvalue = mat.eigen(0);
	matrix eigenvector = mat.eigen(1);

	cout << "eigenvalue :" << endl;
	eigenvalue.show();

	cout << endl;

	cout << "eigenvector :" << endl;
	eigenvector.show();

	cout << endl;

	matrix teigenvector = eigenvector.transpose();

	matrix temp(r,r);
	temp.make_identity_matrix();

	for(i = 0 ; i < r ; ++i)
		temp.set_arr(i,i,eigenvalue.get_arr()[i][0]);
	temp = teigenvector * temp;
	temp = temp * eigenvector;

	cout << "QtDQ" << endl;
	temp.show();
	

	return 0;
}
