#include "matrix.h"

int main(){
	fraction2 temp;
	cin >> temp;
	cout << temp.getLength() << endl;

	cout << "1==================================" << endl;
	temp.getFract().first.test_show();
	cout << "2==================================" << endl;
	temp.getFract().second.test_show();
	return 0;
}
