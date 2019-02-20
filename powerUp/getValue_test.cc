#include "matrix.h"

int main() {
	term t1(4, 2, 3);
	term t2(2, 2, 2);
	terms ts1 = ts1 + t1;
	ts1 = ts1 + t2;
	fraction f1(t1);
	fraction f2(t2);
	cout << f1.getValue() << endl;
	cout << f2.getValue() << endl;
	fraction result;
	cout << result.getValue() << endl;
	result = f1 - f2;
	cout << result.getValue() << endl;

	return 0;
}
