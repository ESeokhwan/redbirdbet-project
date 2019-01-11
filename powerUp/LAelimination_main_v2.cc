#include "matrix.h"

int main(){
	int r,c;
	cin >> r >> c;
	matrix mat(r,c);
	mat.fill();
	mat.show();

	matrix eliminated = mat.eliminate();

	cout << endl;
	cout << "eliminated matrix" << endl;
	eliminated.show();
	
	return 0;
}
