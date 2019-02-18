#include "matrix.h"

int main(){
	int r,c;
	vector<fraction> v;
	cin >> r >> c;
	matrix temp(r,c);

	v = temp.eigenvalue();
	temp.show();

	for(int i = 0 ; i < v.size() ; ++i)
		cout << v[i] << ' ';
	cout << endl;
	return 0;
}

