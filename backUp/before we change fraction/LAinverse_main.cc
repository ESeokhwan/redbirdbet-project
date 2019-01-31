#include "matrix.h"

int main() {
	int r, c;
	cin >> r >> c;
	matrix mat(r,c);
	mat.fill();

	cout << endl;

	mat.show();

	matrix inverse_matrix = mat.inverse_matrix();

	cout << endl;

	cout << "inverse matrix" << endl;

	inverse_matrix.show();

	return 0;
}
