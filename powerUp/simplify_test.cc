#include "matrix.h"

int main() {
	term t1(3,2,6);
	term t2(3,4,27);
	term t3(6,10,2187);
	term t4(3,2,3);
	term t5(3, 2, 30);
	term t6(3, 4, 675);
	term t7(6, 10, 6834375);
	terms ts1;
	ts1 = ts1  + t1 + t2 + t3;
	fraction f1(t4,ts1);
	cout << f1 << endl;
	f1.simplify();
	cout << f1 << endl;
	ts1 = ts1 * t4;
	terms ts2;
	ts2 = ts2 + t5 + t6 + t7;
	fraction f2(ts1, ts2);
	f2.simplify();
	cout << f2 << endl;
	fraction f3(ts1 * t4, ts1);
	cout << f3 << endl;
	f3.simplify();
	cout << f3 << endl;
	return 0;
}
