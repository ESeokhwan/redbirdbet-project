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
	i--;j--;
	pair<int,int> entry1 = arr[i][j], entry2 = arr[i-1][j];
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

matrix eliminatation_matrix(matrix mat) {
	//todo
}



int main(){
	int r,c;
	cin >> r >> c;
	matrix mat(r,c);
	mat.fill();
	mat.show();
	matrix elim21 = remove_entry_matrix(2,1,mat);
	
	cout << endl;
	elim21.show();
	
	matrix result(2,2);
	result = elim21 * mat;
	
	cout << endl;
	result.show();
	return 0;
}
