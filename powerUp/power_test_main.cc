#include "matrix.h"

int main() {
	term t1(2,2,3);
	term t2(3,3,2);
	term t3(2,4,2);
	terms ts1;
	ts1 = ts1 + t1;
	ts1 = ts1 + t2;
	terms ts2;
	ts2 = ts2 + t3;
	fraction f1(make_entry(2, 3));
	fraction f2(make_pair(3, 4));
	fraction f3(ts1, ts2);
	fraction f4(ts1, t1);
	fraction f5(t1, ts1);
	fraction f6(t1, t2);
	fraction f7(ts1, 2);
	fraction f8(2, ts1);
	fraction f9(t1, 2);
	fraction f10(2, t1);
	fraction f11(2,3);
	fraction f12(ts2);
	fraction f13(t1);
	fraction f14(4);
	fraction f15(3.4);
	fraction f16(f15);

	cout << f12.power(2) << endl;
	cout << f12.root(3) << endl;
	return 0;
}
