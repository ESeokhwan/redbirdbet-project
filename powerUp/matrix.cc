#include "matrix.h"
using namespace std;

int matrix::permutation_count = 0;

//simplification of fraction
void simplify(pair<int,int>& p){
	int count = 0;
	int l = p.first > 0 ? p.first : -p.first,
		r = p.second > 0 ? p.second : -p.second;
	int m = l > r ? l : r;

	if((p.first < 0 && p.first*p.second > 0)||p.second==-1){
		p.first = -p.first;
		p.second = -p.second;
	}

	for(int i = m ; i > 1 ; --i)
		if( p.first%i == 0 && p.second%i == 0){
			count++;
			p.first /= i;
			p.second /= i;
		}
}

pair<int,int> operator+(pair<int,int>& l, pair<int,int>& r){
	int num1 = l.first*r.second + l.second*r.first,
		num2 = l.second*r.second;
	pair<int,int> p = make_pair(num1,num2);
	simplify(p);
	return p;
}
pair<int,int> operator-(pair<int,int>& l, pair<int,int>& r){
    int num1 = l.first*r.second - l.second*r.first,
        num2 = l.second*r.second;
    pair<int,int> p = make_pair(num1,num2);
    simplify(p);
    return p;
}
pair<int,int> operator*(pair<int,int>& l, pair<int,int>& r){
	int num1 = l.first*r.first,
		num2 = l.second*r.second;
	pair<int,int> p = make_pair(num1,num2);
	simplify(p);
	return p;
}

void blank(int num){
    for(int i = 0 ; i < num ; ++i) cout << ' ';
}

//to make a better print of pair(such as 3/10).
int countNumberLength(const pair<int,int>& p){
    int len;
    int num1 = p.first , num2 = p.second;
    bool neg = num1 < 0;
    if(num2 == 1) len = 0;
    else{
        len = 1;
        while(num2!=0){
            len++;
            num2 /= 10;
        }
    }

    if(neg){
        len++;
        num1 = -num1;
    }
	if(num1 == 0) len++;

    while(num1!=0){
        len++;
        num1 /= 10;
    }
    return len;
}

matrix operator+ (matrix& l, matrix& r){
	if( l.row != r.row || r.col != l.col ){
		matrix temp(0,0);
		return temp;
	}
	else{
		matrix temp(l.row, r.col);
		for(int i = 0 ; i < l.row ; ++i)
			for(int j = 0 ; j < l.col ; ++j)
				temp.arr[i][j] = l.arr[i][j] + r.arr[i][j];
		return temp;
	}
}

matrix operator- (matrix& l, matrix& r){
	if( l.row != r.row || r.col != l.col ){
		matrix temp(0,0);
		return temp;
	}
	else{
		matrix temp(l.row,l.col);
		for(int i = 0 ; i < l.row ; ++i)
			for(int j = 0 ; j < l.col ; ++j)
				temp.arr[i][j] = l.arr[i][j] - r.arr[i][j];
		return temp;
	}
}

matrix operator* (matrix l, matrix r){
	if(l.col != r.row){
		matrix temp(0,0);
		return temp;
	}
	else{
		matrix temp(l.row, r.col);
		for(int i = 0 ; i < l.row ; ++i){
			for(int j = 0 ; j < r.col ; ++j){
				pair<int,int> p  = make_pair(0,1);
				for(int k = 0 ; k < l.col ; ++k) {
					pair<int,int> q = l.arr[i][k]*r.arr[k][j];
					p = p + q;
				}
				temp.arr[i][j] = p;
			}
		}
		return temp;
	}
}

void matrix::
set_arr (int r, int c, pair<int, int> num) {
	if(arr.size() != 0 && arr[0].size() != 0 && r < row && c < col && r >= 0 && c >= 0) arr[r][c] = num;
}

void matrix::
fill(){
	size_t idx;
	int num1,num2;
	for(int i = 0 ; i < row ; ++i){
		for(int j = 0 ; j < col ; ++j){
			string str;
			cin >> str;
			idx = str.find("/");
			
			if(idx==-1){
				istringstream iss(str);
				iss >> num1;
				arr[i][j] = make_pair(num1,1);
			}
			
			else{
				istringstream iss(str.substr(0,idx) + " " + str.substr(idx+1));
				iss >> num1 >> num2;
				pair<int,int> p = make_pair(num1,num2);
				simplify(p);
				arr[i][j] = p;
			}
		}
	}
}

void matrix::
initialize() {
	for(int i = 0; i < row; i++) {
		vector<pair<int, int> > temp;
		for(int j = 0; j < col; j++)
			temp.push_back(make_pair(0,1));
		arr.push_back(temp);
	}
}

//square matrix일 때만 identity_matrix가 나오게 할까?
void matrix::
make_identity_matrix() {
	initialize();
	for(int i = 0; i < min(row,col); i++)
		arr[i][i] = make_pair(1,1);
}

void matrix::
make_all_entry_zero() {
	for(int i = 0; i < row; i++)
		for(int j = 0; j < col; j++)
			arr[i][j] = make_pair(0,1);
}

void matrix::
show(){
	if(row*col==0) cout << "[]" << endl;
	else{
        int colNum[row] = {0,};
        vector<int> colMax; 
        for(int i = 0 ; i < col ; ++i){
            for(int j = 0 ; j < row ; ++j)
                colNum[j] = countNumberLength(arr[j][i]);
            int max = -1; 
            for(int k = 0 ; k < row ; ++k) max = max > colNum[k] ? max : colNum[k];
            colMax.push_back(max);
        }

        for(int i = 0 ; i < row ; ++i){
            cout << '[' << ' '; 
            for(int j = 0 ; j < col ; ++j){
                blank(colMax[j] - countNumberLength(arr[i][j]));
                if(arr[i][j].second == 1) cout << arr[i][j].first << ' ';
                else cout << arr[i][j].first << '/' << arr[i][j].second << ' ';
            }
            cout << ']' << endl;
        }
    }
}

matrix matrix::
change_two_rows(int row1, int row2) {
	matrix result(this -> get_row(), this -> get_row());
	result.make_all_entry_zero();
	for(int i = 0; i < this -> get_row(); i++) {
		if(i == row1)
			result.set_arr(i, row2, make_pair(1,1));
		else if(i == row2)
			result.set_arr(i, row1, make_pair(1,1));
		else
			result.set_arr(i, i, make_pair(1,1));
	}
	this -> increase_permutation_count();
	return result;
}

matrix matrix::
move_a_row_to_last_row(int row) {
	matrix result(this -> get_row(), this -> get_row());
	
	result.set_arr(this -> get_row() - 1, this -> get_row() - 1, make_pair(0,1));
	result.set_arr(this -> get_row() - 1, row, make_pair(1,1));
	for(int i = row; i < this -> get_row() - 1; i++) {
		result.set_arr(i, i, make_pair(0,1));
		result.set_arr(i, i+1, make_pair(1,1));
	}
//	cout << "permutation" << endl;
//result.show();
	for(int i = row ; i < this -> get_row(); ++i) this -> increase_permutation_count();
	return result;
}

matrix matrix::
remove_entry(int substitution_row, int row, int col) {
	vector< vector< pair<int,int> > > arr = this -> get_arr();
	pair<int,int> entry1 = arr[row][col], entry2 = arr[substitution_row][col];
	pair<int,int> multiflyer = make_pair( -(entry1.first*entry2.second),
								           entry1.second*entry2.first);

	simplify(multiflyer);
	matrix result(this -> get_row(), this -> get_row());
	result.make_all_entry_zero();
	for(int i = 0 ; i < this -> get_row() ; ++i)
		result.set_arr(i, i, make_pair(1,1));
	result.set_arr(row, substitution_row, multiflyer);
	return result;
}

matrix matrix::
eliminate() {
	matrix mat = *this;
	matrix temp;
	bool has_zero_pivot;
	int num_of_pivots = min(mat.get_row(), mat.get_col());
	for(int i = 0; i < num_of_pivots; i++) {
//		cout << "i : " << i << endl;
		for(int j = i; j < mat.get_col(); j++) {
			has_zero_pivot = false;
//			cout << "j : " << j << endl;
			for(int k = i; k < mat.get_row(); k++) {
//				cout << "k : " << k << endl;
				if(mat.get_arr()[i][j].first != 0) break;
				temp = mat.move_a_row_to_last_row(i);
				mat = temp * mat;
//				mat.show();
				if(k == mat.get_row() - 1) has_zero_pivot = true;
//				cout << has_zero_pivot << "k end" << endl;
			}
			if(!has_zero_pivot) {
				for(int k = i+1; k < mat.get_row();k++) {
//					cout << "k2 : " << k << endl;
//					mat.show();
					temp = mat.remove_entry(i, k, j);
					mat = temp * mat;
//					mat.show();
//					cout << "k2 end"  << endl;
				}
				break;
			}
//			cout << "j end" << endl;
		}
//		cout << "i end" << endl;
	}
	return mat;
}

matrix matrix::
permutation_matrix() {
	matrix mat = *this;
	matrix permutation_matrix(row, row);
	matrix temp;
	bool has_zero_pivot;
	int num_of_pivots = min(mat.get_row(), mat.get_col());
	for(int i = 0; i < num_of_pivots; i++) {
		for(int j = i; j < mat.get_col(); j++) {
			has_zero_pivot = false;
			for(int k = i; k < mat.get_row(); k++) {
				if(mat.get_arr()[i][j].first != 0) break;
				temp = mat.move_a_row_to_last_row(i);
				permutation_matrix = temp * permutation_matrix;
				mat = temp * mat;
				if(k == mat.get_row() - 1) has_zero_pivot = true;
			}
			if(!has_zero_pivot) {
				for(int k = i+1; k < mat.get_row();k++) {
					temp = mat.remove_entry(i, k, j);
					mat = temp * mat;
				}
				break;
			}
		}
	}
	return permutation_matrix;
}

matrix matrix::
elimination_matrix() {
	matrix mat = permutation_matrix() * *this;
	matrix elimination_matrix(row, row);
	matrix temp;
	int num_of_pivots = min(col, row);
	int num_of_zeropivots = 0;
	for(int i = 0; i < num_of_pivots; i++) {
		while(mat.arr[i][i+num_of_zeropivots] == make_pair(0,1))
			num_of_zeropivots++;
		for(int j = i+1; j < row; j++) {
			temp = mat.remove_entry(i, j, i+num_of_zeropivots);
			mat = temp * mat;
			elimination_matrix = temp * elimination_matrix;
		}
	}
	return elimination_matrix;
}

matrix matrix::
transpose() {
	matrix mat(col, row);
	for(int i = 0; i < row; i++)
		for(int j = 0; j < col; j++)
			mat.arr[j][i] = arr[i][j];
	return mat;
} 

//matrix matrix::
//get_permutation_matrix() {
//	eliminate();
//	return *permutation_matrix_ptr;
//}

//matrix matrix::
//get_elimination_matrix() {
//	eliminate();
//	return *Felimination_matrix_ptr;
//}


