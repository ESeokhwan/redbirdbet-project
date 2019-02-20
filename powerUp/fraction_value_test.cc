#include "matrix.h"

int main() {
	term t1(2,2,3);
	term t2(3,3,2);
	term t3(2,1,1);
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

	cout << "1 " << endl;
	cout << f1 << " " << f1.getValue() << endl;

	cout << "2 " << endl;
	cout << f2 << " " <<  f2.getValue() << endl;

	cout << "3 " << endl;
	cout << f3 << " " << f3.getValue() << endl;

	cout << "4 " << endl;
	cout << f4 << " " <<f4.getValue() << endl;

	cout << "5 " << endl;
	cout << f5 << " " << f5.getValue() << endl;

	cout << "6 " << endl;
	cout << f6 << " " << f6.getValue() << endl;

	cout << "7 " << endl;
	cout << f7 << " " << f7.getValue() << endl;

	cout << "8 " << endl;
	cout << f8 << " " << f8.getValue() << endl;

	cout << "9 " << endl;
	cout << f9 << " " << f9.getValue() << endl;

	cout << "10 " << endl;
	cout << f10 << " " << f10.getValue() << endl;

	cout << "11 " << endl;
	cout << f11 << " " << f11.getValue() << endl;

	cout << "12 " << endl;
	cout << f12 << " " << f12.getValue() << endl;

	cout << "13 " << endl;
	cout << f13 << " " << f13.getValue() << endl;

	cout << "14 " << endl;
	cout << f14 << " " << f14.getValue() << endl;

	cout << "15 " << endl;
	cout << f15 << " " << f15.getValue() << endl;

	cout << "16 " << endl;
	cout << f16 << " " << f16.getValue() << endl;

	f7 = make_entry(2, 3);
	f6 = make_pair(3, 4);
	f5 = ts2;
	f4 = t1;
	f3 = 4;
	f2 = 3.4;
	f1 = f15;

	cout << "1 " << endl;
	cout << f1 << " " << f1.getValue() << endl;

	cout << "2 " << endl;
	cout << f2 << " " <<  f2.getValue() << endl;

	cout << "3 " << endl;
	cout << f3 << " " << f3.getValue() << endl;

	cout << "4 " << endl;
	cout << f4 << " " <<f4.getValue() << endl;

	cout << "5 " << endl;
	cout << f5 << " " << f5.getValue() << endl;

	cout << "6 " << endl;
	cout << f6 << " " << f6.getValue() << endl;

	cout << "7 " << endl;
	cout << f7 << " " << f7.getValue() << endl;

	return 0;
}
