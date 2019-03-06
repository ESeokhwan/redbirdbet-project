#include "matrix.cc"
#define NUM_OF_ACTION 18

int main() {
	bool quit = false;
	string yes_or_no;
	string* action[NUM_OF_ACTION] =
		{"0. Readme.txt",
		 "1. Matrix addition",
    	 "2. Matrix substitution",
		 "3. Matrix multiplication",
		 "4 .Matrix elimination",
		 "5. Inverse matrix",
		 "6. LU factorization",
		 "7. RREF",
		 "8. Complete solution (Ax = b)",
		 "9. Projection matrix",
		 "10. Gram-Schmidt",
		 "11. QR factorization",
		 "12. Determinant",
		 "13. Eigenvalue",
		 "14. Eigenvector",
		 "15. Diagonalization",
		 "16. Markov matrix",
		 "17. Single value decomposition"};

	while(quit == false) {
		int mode;
		cout << "What do you want to do?" << endl;
		for(int i = 0; i < NUM_OF_ACTION; i++)
			cout << i << ". " << action[i] << endl;
		cin >> mode;
		while(cin.fail() || mode >= NUM_OF_ACTION || mode < 0) {
			cout << "Worng input. Please give me correct input" << endl;
			cin >> mode;
		}

		int col, row;
		cout << "input row : " << endl;
		cin >> row;
		cout << "input column : " << endl;
		cin >> col;

		matrix mat1(row, col);
		cout << "input " << row << " by " << col << "matrix" << endl;
		mat.fill();

		/*
		cout << "input row : " << endl;
		cin >> row;
		cout << "input column : " << endl;
		cin >> col;

		matrix mat2(row, col);
		cout << "input " << row << " by " << col << "matrix" << endl;
		mat2.fill();
		*/

		//여기에 case문을 쓰던 if문을 쓰던 1번 부터 17번까지 구현하기


		cout << "Do you have another work to do(y or n)" << endl;
		cin >> yes_or_no;
		while(cin.fail()||yes_or_no != "y" || yes_or_no != "n") {
			cout << "Give correct input(y or n)\n Do you have another work?" << endl;
			cin >> yes_or_no;
		}
		if(yes_or_no == "n")
			quit = true;
	}
	return 0;
}
