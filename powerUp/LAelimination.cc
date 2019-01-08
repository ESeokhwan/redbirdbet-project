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
	result.set_arr(row, row, make_pair(0,1));
	result.set_arr(row, mat.get_row() - 1, make_pair(1,1));
	for(int i = row + 1; i < mat.get_row(); i++) {
		result.set_arr(i, i-1, make_pair(1,1));
		result.set_arr(i, i, make_pair(0,1));
	}
	return result;
}

matrix remove_entry_matrix(int i, int j, matrix& mat){
	vector< vector< pair<int,int> > > arr = mat.get_arr();
//	i--;j--;
	pair<int,int> entry1 = arr[i][j], entry2 = arr[j][j];//바 꿈 but have to change again for rref I think
	pair<int,int> multifier;
	if(entry2.first > 0)
		multifier = make_pair( -(entry1.first*entry2.second),
								entry1.second*entry2.first);
	else
		multifier = make_pair( (entry1.first*entry2.second),
				               -entry1.second*entry2.first);
	simplify(multifier);
	matrix result(mat.get_row(), mat.get_row());
	result.initialize();
	for(int k = 0 ; k < mat.get_row() ; ++k)
		result.set_arr(k, k, make_pair(1,1));
	result.set_arr(i, j, multifier);
	return result;
}

matrix eliminate(matrix mat) {
	matrix temp;
	bool has_zero_pivot;
	int num_of_pivots = min(mat.get_row(), mat.get_col());
	for(int i = 0; i < num_of_pivots; i++) {
		cout << "i : " << i << endl;
		has_zero_pivot = false;
		for(int j = i; j < mat.get_row();j++) {
			cout << "j : " << j << endl;
			if(mat.get_arr()[i][i].first != 0) break;
			temp = move_to_last_row(mat, i);
			mat = temp * mat;
			if(j == mat.get_row() - 1) has_zero_pivot = true;
			cout << "j end" << endl;
		}
		if(has_zero_pivot == false) {
			for(int j = i+1; j < mat.get_row();j++) {
				cout << "j2 : " << j << endl;
				temp = remove_entry_matrix(j,i,mat);
				mat = temp * mat;
				mat.show();
				cout << "j2 end"  << endl;
			}
		}
		else break;//to do for rref
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
