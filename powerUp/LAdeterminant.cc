#include "LAelimination.h"
#include <iostream>
using namespace std;

int matrix::permutation_count = 0;

pair<int,int> determinant(matrix& mat){
	if(mat.get_row() != mat.get_col()){
		cout << "not square matrix" << endl;
		return make_pair(-1,1);
	}

	else{
		matrix temp;
		pair<int,int> result = make_pair(1,1);
		bool is_permuation_odd;
		temp = eliminate(mat);
		for(int i = 0 ; i < temp.get_row() ; ++i){
			pair<int,int> mul = temp.get_arr()[i][i];
			result = result * mul;
		}
		is_permuation_odd = temp.get_per_count()%2;
		if(is_permuation_odd) result.first = -result.first;
		return result;
	}
}
			

int main(){
	int row,col;
	cin >> row >> col;
	matrix mat(row, col);

	mat.fill();

	cout << endl;
	mat.show();
	
	cout << endl;
	pair<int,int> det = determinant(mat);
	if(det.second==1)
		cout << "det(matrix) = " << det.first << endl;
	else
		cout << "det(matrix) = " << det.first << '/' << det.second << endl;
	return 0;
}
