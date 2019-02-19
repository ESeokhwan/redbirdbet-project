#include "matrix.h"

int main(){
	try {
		int col, row;
		cin >> row >> col;
		matrix mat(row, col);
		mat.fill();
		
		cout << endl;
		mat.show();
	
		cout << endl;
		matrix result = mat.gram_schmidt();
		result.show();
	}
	catch(char const* e) {
		cout << e << endl;
	}

	return 0;
}
