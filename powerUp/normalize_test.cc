#include "matrix.h"


int main() {

	terms l(156);
	l.test_show();

	fraction test(1);
	cout << test << endl;

	test = test + 3;
	cout << test << endl;

	matrix mat(4, 1);
	
	mat.fill();

	mat = mat.normalize();
	mat.show();

	return 0;
}
	

