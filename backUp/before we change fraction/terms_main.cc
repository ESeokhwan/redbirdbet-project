#include "matrix.h"

int main() {
	try {
		term term1(2, 6, 12960000);
		term term2(1, 2, 48);
		term term3(6);
		term term4(2, 3, 450);
		term term5(4,16);
		term term6(2, 0);
		term term7(2, 1);
		cout << "a" << endl;

		terms result;
		result = result + term1;
		cout << "b" << endl;
		result.test_show();
		result = result + term2;
		cout << "c" << endl;
		result.test_show();
		result = result + term3;
		cout << "d" << endl;
		result.test_show();
		result = result + term4;
		cout << "e" << endl;
		result.test_show();
		result = result + term5;
		cout << "f" << endl;
		result.test_show();
		result = result + term6;
		cout << "g" << endl;
		result.test_show();
		result = result + term7;
		cout << "h" << endl;

		result.test_show();
	}
	catch(char const* e) {
		cout << e << endl;
	}

	return 0;
}
