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
	result.set_arr(row, row. make_pair(0,1));
	result.set_arr(row, mat.get_row() - 1, make_pair(1,1));
	for(int i = row + 1; i < mat.get_row(); i++) {
		result.set_Arr(i, i-1, make_pair(1,1));
		result.set_Arr(i, i, make_pair(0,1));
	}
	return result;
}

		

matrix eliminatation_matrix(matrix mat) {
	//todo
}


	
