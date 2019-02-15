#include "matrix.h"

int main(){
	int row, col, i = 0, j = 0;
	cin >> row >> col;
	fraction2 arr[row*col];

	for(i = 0 ; i < row ; ++i)
		for(j = 0 ; j < col ; ++j)
			cin >> arr[i*col + j];
	fraction2_output(arr,row,col);

	return 0;
}
