#include "matrix.h"

int main(){
	fraction2 temp;
	cin >> temp;
	pair<int, string> tmp = temp.fts();
	cout << tmp.first << endl;
	for(int i = 0 ; i < tmp.first 	; ++i) cout << i%10;
	cout << endl;
	cout << tmp.second << endl;

	cout << endl << endl << endl;
	temp.simplify();
	tmp = temp.fts();
	cout << tmp.first << endl;
	for(int i = 0 ; i < tmp.first   ; ++i) cout << i%10;
	cout << endl;
	cout << tmp.second << endl;

	return 0;
}
