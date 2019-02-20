#include "matrix.h"

int main(){
	try {
		int col, row;
		cin >> row >> col;
		matrix mat(row, col);
		mat.fill();
		
		cout << endl;
		cout << "A" << endl;
		mat.show();
	
		cout << endl;
		cout << "Q" << endl;
		mat.gram_schmidt().show();

		cout << endl;
		cout << "R" << endl;
		mat.Rfactor().show();
	}
	catch(char const* e) {
		cout << e << endl;
	}

	return 0;
}
