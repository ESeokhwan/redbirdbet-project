#include "matrix.h"

int main(){
	int r,c;
	cin >> r >> c;
	matrix mat(r,c);
	mat.fill();

	cout << endl;
	mat.show();

	cout << endl;
	mat.show(1);

	matrix eliminated = mat.eliminate();

	cout << endl;
	cout << "eliminated matrix" << endl;
	eliminated.show();

	cout << endl;
	cout << "permutation_matrix" << endl;
	mat.permutation_matrix().show();

	cout << endl;
	cout << "elimination_matrix" << endl;
	mat.elimination_matrix().show();
	
	return 0;
}
