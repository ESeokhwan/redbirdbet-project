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
		cout << endl;

		term _term1(3, 3, 2);
		term _term2(1, 2, 3);

		terms result1;
		result1 = result1 + _term1;
		cout << "i" << endl;
		result1 = result1 + _term2;
		cout << "j" << endl;

//		cout << "k" << endl;
//		result1 = (_term1 + _term2);
//		cout << "l" << endl;

		result1.test_show();

		cout << "AAA" << endl;
		
		terms result2;
		result2 = result1 * result;
		result2.test_show();

		cout << "BBB" << endl;

		term __term1(3,3,2);
		term __term2(6,3,450);

		term result3;
		result3 = __term1*__term2;
		result3.test_show();

	}
	catch(char const* e) {
		cout << e << endl;
	}

	return 0;
}
