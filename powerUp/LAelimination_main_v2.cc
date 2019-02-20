#include "matrix.h"

int main(){
	int r,c;
	cin >> r >> c;
	matrix mat(r,c);
	mat.fill();

	cout << endl;
	mat.show();
	mat.show_double();

	cout << endl;
	mat.show(1);

	matrix eliminated = mat.eliminate();

	cout << endl;
	cout << "eliminated matrix" << endl;
	eliminated.show();
	cout << "double" << endl;
	eliminated.show_double();
	cout << "?? : " << eliminated.get_arr()[2][1].getValue() << endl;

	cout << endl;
	cout << "permutation_matrix" << endl;
	mat.permutation_matrix().show();
	cout << "double" << endl;
	mat.permutation_matrix().show_double();

	cout << endl;
	cout << "elimination_matrix" << endl;
	mat.elimination_matrix().show();
	mat.elimination_matrix().show_double();
	
	return 0;
}
