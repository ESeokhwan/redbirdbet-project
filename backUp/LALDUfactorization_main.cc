#include "matrix.h"

int main() {
	int r,c;
	cin >> r >> c;
	matrix mat(r,c);
	mat.fill();
	cout << endl;

	mat.LDUfactorization();

	return 0;
}

