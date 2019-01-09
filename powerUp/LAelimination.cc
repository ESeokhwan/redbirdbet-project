#include "LAelimination.h"

matrix permutation_matrix(matrix mat, int row1, int row2) {
	matrix result(mat.get_row(), mat.get_row());
	result.initialize();
	for(int i = 0; i < mat.get_row(); i++) {
		if(i == row1)
			result.set_arr(i, row2, make_pair(1,1));
		else if(i == row2)
			result.set_arr(i, row1, make_pair(1,1));
		else
			result.set_arr(i, i, make_pair(1,1));
	}
	return result;
}

matrix move_to_last_row(matrix mat, int row) {
	matrix result(mat.get_row(), mat.get_row());
	result.initialize();
	for(int i = 0; i < mat.get_row(); i++)
		result.set_arr(i, i, make_pair(1,1));
	result.set_arr(mat.get_row() - 1, mat.get_row() - 1, make_pair(0,1));
	result.set_arr(mat.get_row() - 1, row, make_pair(1,1));
	for(int i = row; i < mat.get_row() - 1; i++) {
		result.set_arr(i, i, make_pair(0,1));
		result.set_arr(i, i+1, make_pair(1,1));
	}
	cout << "permutation" << endl;
	result.show();
	return result;
}

matrix remove_entry_matrix(matrix& mat, int substitution_row, int row, int col){
	vector< vector< pair<int,int> > > arr = mat.get_arr();
	pair<int,int> entry1 = arr[row][col], entry2 = arr[substitution_row][col];//바 꿈 but have to change again for rref I think
	pair<int,int> multiflyer = make_pair( -(entry1.first*entry2.second),
								           entry1.second*entry2.first);

	simplify(multiflyer);
	matrix result(mat.get_row(), mat.get_row());
	result.initialize();
	for(int i = 0 ; i < mat.get_row() ; ++i)
		result.set_arr(i, i, make_pair(1,1));
	result.set_arr(row, substitution_row, multiflyer);
	return result;
}

matrix eliminate(matrix mat) {
	matrix temp;
	bool has_zero_pivot;
	int num_of_pivots = min(mat.get_row(), mat.get_col());
	for(int i = 0; i < num_of_pivots; i++) {
		cout << "i : " << i << endl;
		for(int j = i; j < mat.get_col(); j++) {
			has_zero_pivot = false;
			cout << "j : " << j << endl;
			for(int k = i; k < mat.get_row(); k++) {
				cout << "k : " << k << endl;
				if(mat.get_arr()[i][j].first != 0) break;
				temp = move_to_last_row(mat, i);
				mat = temp * mat;
				if(k == mat.get_row() - 1) has_zero_pivot = true;
				cout << has_zero_pivot << "k end" << endl;
			}
			if(!has_zero_pivot) {
				for(int k = i+1; k < mat.get_row();k++) {
					cout << "k2 : " << k << endl;
					mat.show();
					temp = remove_entry_matrix(mat, i, k, j);
					mat = temp * mat;
					mat.show();
					cout << "k2 end"  << endl;
				}
				break;
			}
			cout << "j end" << endl;
		}
		cout << "i end" << endl;
	}
	return mat;
}

matrix eliminatation_matrix(matrix mat) {
	//todo
}



int main(){
	int r,c;
	cin >> r >> c;
	matrix mat(r,c);
	mat.fill();
	mat.show();
	cout << "a" << endl;

	matrix eliminated = eliminate(mat);
		
	cout << endl;
	eliminated.show();
	
	return 0;
}
