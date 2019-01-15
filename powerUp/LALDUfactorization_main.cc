#include "matrix.h"

int main() {
	int r,c;
	cin >> r >> c;
	matrix mat(r,c);
	mat.fill();

	mat.LDUfactorization();

	return 0;
}

