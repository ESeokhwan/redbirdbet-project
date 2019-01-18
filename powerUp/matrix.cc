#include "matrix.h"
using namespace std;

int matrix::permutation_count = 0;

fraction::
fraction() : fract(make_pair(1,1)), length(1) { }

fraction::
fraction(pair<int, int> p) {
	fract = p;
	setLength();
}

fraction::
fraction(int num) {
	fract = make_pair(num, 1);
	setLength();
}

fraction::
fraction(int num1, int num2) {
	fract = make_pair(num1, num2);
	setLength();
}

fraction::
fraction(const fraction& rhs){
	fract = rhs.fract; length = rhs.length;
}


//simplification of fraction
void fraction::
simplify(){
	int count = 0;
	int l = fract.first > 0 ? fract.first : -fract.first,
		r = fract.second > 0 ? fract.second : -fract.second;
	int m = l > r ? l : r;

	if((fract.first < 0 && fract.first*fract.second > 0) || fract.second==-1){
		fract.first = -fract.first;
		fract.second = -fract.second;
	}
	if( fract.second < 0 && fract.first > 0){
		fract.first = -fract.first;
		fract.second =-fract.second;
	}

	for(int i = m ; i > 1 ; --i)
		if( fract.first%i == 0 && fract.second%i == 0){
			count++;
			fract.first /= i;
			fract.second /= i;
		}
	setLength();
}

int fraction::
getLength() {
	return length;
}

bool fraction::
is_zero() {
	return fract.first == 0;
}

bool operator==(const int& numL, const fraction& fracR) {
	if(fracR.fract.second == 0)
		return false;
	if((fracR.fract.first)%(fracR.fract.second) == 0)
		if(fracR.fract.first/fracR.fract.second == numL)
			return true;
	return false;
}

bool operator!=(const int& numL, const fraction& fracR) {
	if(numL == fracR)
		return false;
	return true;
}

bool operator==(const fraction& fracL, const int& numR) {
	return numR == fracL;
}

bool operator!=(const fraction& fracL, const int& numR) {
	return numR != fracL;
}

bool operator==(const double& numL, const fraction& fracR) {
	if(fracR.fract.second == 0)
		return false;
	if((double)fracR.fract.first/(double)fracR.fract.second == numL)
		return true;
	return false;
}

bool operator!=(const double& numL, const fraction& fracR) {
	if(numL == fracR)
		return false;
	return true;
}

bool operator==(const fraction& fracL, const double& numR) {
	return numR == fracL;
}

bool operator==(const float& numL, const fraction& fracR) {
	if(fracR.fract.second == 0)
		return false;
	if((float)fracR.fract.first/(float)fracR.fract.second == numL)
		return true;
	return false;
}

bool operator!=(const float& numL, const fraction& fracR) {
	if(numL == fracR)
		return false;
	return true;
}

bool operator==(const fraction& fracL, const float& numR) {
	return numR == fracL;
}

bool operator!=(const fraction& fracL, const float& numR) {
	return numR != fracL;
}

bool operator==(const pair<int, int>& pairL, const fraction& fracR) {
	fraction temp(pairL.first, pairL.second);
	return temp == fracR;
}

bool operator!=(const pair<int, int>& pairL, const fraction& fracR) {
	if(pairL == fracR)
		return false;
	return true;
}

bool operator==(const fraction& fracL, const pair<int, int>& pairR) {
	return pairR == fracL;
}

bool operator!=(const fraction& fracL, const pair<int, int>& pairR) {
	return pairR != fracL;
}

bool operator==(const fraction& fracL, const fraction& fracR) {
	fraction temp1(fracL);
	fraction temp2(fracR);
	temp1.simplify();
	temp2.simplify();
	if(temp1.fract.first == temp2.fract.first &&
			temp1.fract.second == temp2.fract.second)
		return true;
	return false;
}

bool operator!=(const fraction& fracL, const fraction& fracR) {
	if(fracL == fracR)
		return false;
	return true;
}

fraction operator+(const fraction& l, const fraction& r){
	int num1 = l.fract.first * r.fract.second + l.fract.second*r.fract.first,
		num2 = l.fract.second*r.fract.second;
	fraction p( make_pair(num1,num2) );
	p.simplify();
	return p;
}
fraction operator-(const fraction& l, const fraction& r){
    int num1 = l.fract.first * r.fract.second - l.fract.second*r.fract.first,
		num2 = l.fract.second*r.fract.second;

    fraction p( make_pair(num1,num2) );
    p.simplify();
    return p;
}
fraction operator*(const fraction& l, const fraction& r){
	int num1 = l.fract.first * r.fract.first,
		num2 = l.fract.second * r.fract.second;
	fraction p( make_pair(num1,num2) );
	p.simplify();
	return p;
}
fraction operator/(const fraction& l, const fraction& r){
	fraction reverse_r( make_pair(r.fract.second , r.fract.first));
	fraction result = l * reverse_r;
	return result;
}
fraction operator-(const fraction& rhs){
	fraction result(-rhs.fract.first,rhs.fract.second); 
	return result;
}
ostream& operator<<(ostream& out, const fraction& rhs){
	if(rhs.fract.second == 1) return out << rhs.fract.first << ' ';
	else return out << rhs.fract.first << '/' << rhs.fract.second << ' ';
}

istream& operator>>(istream& in, fraction& rhs){
 	size_t idx;
	int num1,num2;
	string str;
	cin >> str;
	idx = str.find("/");
	bool is_integer = (idx==-1);

	if(!is_integer) str = str.substr(0,idx) + " " + str.substr(idx+1);
	istringstream iss(str);

	if(is_integer){
 		iss >> num1;
		rhs.fract = make_pair(num1,1);
	}
	else{
	   	iss >> num1 >> num2;
		rhs.fract = make_pair(num1,num2);
	}

 	rhs.simplify();
}
		
void blank(int num){
    for(int i = 0 ; i < num ; ++i) cout << ' ';
}
//instead of make_pair
fraction make_entry(int num1, int num2){
	fraction result(num1,num2); 
	return result;
}
//to make a better print of pair(such as 3/10).
void fraction::
setLength(){
    int len;
    int num1 = fract.first , num2 = fract.second;
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
    length = len;
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
				fraction p(make_pair(0,1));
				for(int k = 0 ; k < l.col ; ++k) {
					fraction q = l.arr[i][k]*r.arr[k][j];
					p = p + q;
				}
				temp.arr[i][j] = p;
			}
		}
		return temp;
	}
}

matrix operator* (const fraction& fracL, const matrix& matR) {
	matrix result(matR.row, matR.col);
	for(int i = 0; i < matR.row; i++) 
		for(int j = 0; j < matR.col; j++) 
			result.arr[i][j] = fracL * matR.arr[i][j];
	return result;
}

matrix operator* (const matrix& matL, const fraction& fracR) {
	return fracR * matL;
}

matrix operator* (const int& intL, const matrix& matR) {
	return fraction(intL) * matR;
}

matrix operator* (const matrix& matL, const int& intR) {
	return intR * matL;
}

bool operator== (const matrix& matL, const matrix& matR) {
	if(matL.row != matR.row || matL.col != matR.col)
		return false;
	for(int i = 0; i < matL.row; i++) 
		for(int j = 0; j < matL.col; j++) 
			if(matL.arr[i][j] != matR.arr[i][j]) 
				return false;
	return true;
}

bool operator!= (const matrix& matL, const matrix& matR) {
	if(matL == matR)
		return false;
	return true;
}

fraction dotproduct(const matrix& matL, const matrix& matR) {
	if(matL.row != matR.row || matL.col != matR.col)
		throw exception();
	matrix temp;
	temp = matL.transpose();
	return (temp * matR).arr[0][0];
}

matrix::
matrix() : row(0), col(0) { }

matrix::
matrix(int r, int c) : row(r), col(c) {
	make_identity_matrix();
}

matrix::
matrix(const matrix& mat) {
	row = mat.row;
	col = mat.col;
	arr = mat.arr;
}

matrix::
~matrix() {
//	delete permutation_matrix_ptr;
//	delete elimination_matrix_ptr;
}

int matrix::
get_row() {
	return row;
}

int matrix::
get_col() {
	return col;
}

vector < vector < fraction > > matrix::
get_arr() {
	return arr;
}

int matrix::
get_permutation_count() {
	return permutation_count;
}

void matrix::
increase_permutation_count(){
	permutation_count++;
}

matrix& matrix::
operator=(const matrix& rhs){
	row = rhs.row;
	col = rhs.col;
	arr = rhs.arr;
}

void matrix::
set_arr (int r, int c, fraction num) {
	if(arr.size() != 0 && arr[0].size() != 0 && r < row && c < col && r >= 0 && c >= 0) arr[r][c] = num;
}

void matrix::
fill(){
	for(int i = 0 ; i < row ; ++i)
		for(int j = 0 ; j < col ; ++j)
			cin >> arr[i][j];
}

void matrix::
initialize() {
	fraction f(make_pair(0,1));
	vector<fraction> temp;
	for(int i = 0 ; i < col ; ++i) temp.push_back(f);
	for(int i = 0 ; i < row ; ++i) arr.push_back(temp);
}

//square matrix일 때만 identity_matrix가 나오게 할까?
void matrix::
make_identity_matrix() {
	initialize();
	fraction f(make_pair(1,1));
	for(int i = 0; i < min(row,col); i++)
		arr[i][i] = f;
}

void matrix::
make_all_entry_zero() {
	fraction zero_entry(make_pair(0,1));
	for(int i = 0; i < row; i++)
		for(int j = 0; j < col; j++)
			arr[i][j] = zero_entry;
}

void matrix::
show(bool no_paranthesis){
	if(row*col==0) cout << "[]" << endl;
	else{
        int colNum[row] = {0,};
        vector<int> colMax; 
        for(int i = 0 ; i < col ; ++i){
            for(int j = 0 ; j < row ; ++j)
                colNum[j] = arr[j][i].getLength();
            int max = -1; 
            for(int k = 0 ; k < row ; ++k) max = max > colNum[k] ? max : colNum[k];
            colMax.push_back(max);
        }

        for(int i = 0 ; i < row ; ++i){
			if(!no_paranthesis) cout << '[' << ' '; 
			else cout << ' ';
            for(int j = 0 ; j < col ; ++j){
                blank(colMax[j] - arr[i][j].getLength());
                cout << arr[i][j];
            }
			if(!no_paranthesis) cout << ']' << endl;
			else cout << endl;
        }
    }
}


void matrix::
matrix_simplification(){
	for(int i = 0 ; i < row ; ++i)
		for(int j = 0 ; j < col ; ++j)
			arr[i][j].simplify();
}

matrix matrix::
change_two_rows(int row1, int row2) {
	matrix result(this -> get_row(), this -> get_row());
	result.make_all_entry_zero();
	for(int i = 0; i < this -> get_row(); i++) {
		if(i == row1)
			result.set_arr(i, row2, make_entry(1,1));
		else if(i == row2)
			result.set_arr(i, row1, make_entry(1,1));
		else
			result.set_arr(i, i, make_entry(1,1));
	}
	this -> increase_permutation_count();
	return result;
}

matrix matrix::
move_a_row_to_last_row(int row) {
	matrix result(this -> get_row(), this -> get_row());
	
	result.set_arr(this -> get_row() - 1, this -> get_row() - 1, make_pair(0,1));
	result.set_arr(this -> get_row() - 1, row, make_entry(1,1));
	for(int i = row; i < this -> get_row() - 1; i++) {
		result.set_arr(i, i, make_entry(0,1));
		result.set_arr(i, i+1, make_entry(1,1));
	}
//	cout << "permutation" << endl;
//result.show();
	for(int i = row ; i < this -> get_row(); ++i) this -> increase_permutation_count();
	return result;
}

matrix matrix::
remove_entry(int substitution_row, int row, int col) {
	vector< vector<fraction> > arr = this -> get_arr();
	fraction entry1 = arr[row][col], entry2 = -arr[substitution_row][col];
    fraction multiflyer = entry1 / entry2;

	multiflyer.simplify();
	matrix result(this -> get_row(), this -> get_row());
	result.make_all_entry_zero();
	for(int i = 0 ; i < this -> get_row() ; ++i)
		result.set_arr(i, i, make_entry(1,1));
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
				if(!mat.get_arr()[i][j].is_zero()) break;
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
				if(!mat.get_arr()[i][j].is_zero()) break;
				temp = mat.move_a_row_to_last_row(i);
				permutation_matrix = temp * permutation_matrix;
				mat = temp * mat;
				if(k == mat.get_row() - 1) has_zero_pivot = true;
			}
			if(!has_zero_pivot) {
				for(int k = i+1; k < mat.get_row();k++) {
					temp = mat.remove_entry(i, k, j);
					mat = temp * mat;
					mat = mat.remove_entry(i,k,j) * mat;
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
		while(mat.arr[i][i+num_of_zeropivots].is_zero())
			num_of_zeropivots++;
		for(int j = i+1; j < row; j++) {
			temp = mat.remove_entry(i, j, i+num_of_zeropivots);
			mat = temp * mat;
			elimination_matrix = temp * elimination_matrix;
		}
	}
	elimination_matrix.matrix_simplification();
	return elimination_matrix;
}

//P와 D가 identity일 때 안 출력되게 업글하기
bool matrix::
LDUfactorization() {
	if(row != col) {
		cout << "You can't do LDU factorization." << endl;
		return false;
	}
	if(permutation_matrix() != matrix(row,row)) {
		cout << "P" << endl;
		permutation_matrix().show();
		cout << endl;
	}

	cout << "A" << endl;
	show();
	cout << endl;

	cout << "L" << endl;
	elimination_matrix().inverse_matrix().show();
	cout << endl;

	matrix upper_triangle = eliminate();
	matrix diagonal = matrix(row, row);
	for(int i = 0; i < row; i++) {
		diagonal.arr[i][i] = upper_triangle.arr[i][i];
		for(int j = i; j < row; j++)
			upper_triangle.set_arr(i, j, upper_triangle.arr[i][j] / upper_triangle.arr[i][i]);
	}

	if(diagonal != matrix(row, row)) {
		cout << "D" << endl;
		diagonal.show();
		cout << endl;
	}

	cout << "U" << endl;
	upper_triangle.show();
	cout << endl;

	return true;
}

matrix matrix::
inverse_matrix() {
	matrix eliminated;
	matrix result;
	matrix remove_entry;
	bool singular = false;
	if(row != col)
		return result;
	else {
		eliminated = this -> eliminate();
		for(int i = 0; i < row; i++) {
			if(eliminated.arr[i][i] == 0) {
				singular = true;
				return result;
			}
		}
	}
	matrix elimination_matrix = this -> elimination_matrix();
	for(int i = row - 1; i >= 0; i--) {
		for(int j = i - 1; j >= 0; j--) {
			remove_entry = eliminated.remove_entry(i, j, i);
			elimination_matrix = remove_entry * elimination_matrix;
			eliminated = remove_entry * eliminated;
		}
	}
	matrix inverse_of_diagonal(row, row);
	for(int i = 0; i < row; i++) {
		fraction one;
		inverse_of_diagonal.set_arr(i, i, one / eliminated.arr[i][i]);
	}

	matrix permutation_matrix = this -> permutation_matrix();
	result = elimination_matrix * permutation_matrix;
	result = inverse_of_diagonal * result;
	return result;
}

matrix matrix::
transpose() const {
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

fraction matrix::
get_determinant(){
	return determinant;
}

void matrix::
find_determinant(){
	if(row!=col)
		cout << "not a square matrix" << endl;
	else{
		matrix temp = *this;
		fraction result(1,1);
		temp = temp.eliminate();
		for(int i = 0 ; i < temp.get_row() ; ++i)
			result = result * temp.get_arr()[i][i];
		this -> determinant = result;
	}
}

matrix matrix::
RREF(){
	matrix temp = *this;
	temp = this -> eliminate();
	int pivot[temp.get_row()] = {0,};

	for(int i = 0 ; i <  temp.get_row() ; ++i)
		for(int j = 0 ; j < temp.get_col() ; ++j)
			if(!temp.get_arr()[i][j].is_zero()){
				pivot[i] = j;
				break;
			}
	for(int i = 0 ; i < temp.get_row() ; ++i){
		if(i!=0&&pivot[i]==0) continue;
		for(int j = i ; j > 0 ; --j){
			temp = temp.remove_entry(i,j-1,pivot[i]) * temp;
		}
	}

	for(int i = 0 ; i < temp.get_row() ; ++i){
		fraction div = temp.get_arr()[i][ pivot[i] ];

		for(int j = pivot[i] ; j < temp.get_col() ; ++j){
			if(div.is_zero()) break;
			fraction temp_fraction = temp.get_arr()[i][j] / div;
			temp.set_arr(i,j,temp_fraction);
		}
	}

	//cout << endl << "RREF" << endl;
	temp.matrix_simplification();
	//temp.show();
	return temp;
}

matrix matrix::
null_space(){
	matrix temp = this -> RREF();

	int pivot[temp.get_row()] = {0,};
	int num_pivot = 0;

	for(int i = 0 ; i <  temp.get_row() ; ++i)
		for(int j = 0 ; j < temp.get_col() ; ++j){
			if(!temp.get_arr()[i][j].is_zero()){
				pivot[i] = j;
				break;
			}
			else
				pivot[i] = -1;
		}

	for(int i = 0 ; i < temp.get_row() ; ++i)
		if(pivot[i] != -1) num_pivot++;

	int permutate_column[temp.get_col()] = {0,};
	for(int i = 0 ; i < temp.get_col() ; ++i) permutate_column[i] = i;

	for(int i = 0 ; i < num_pivot ; ++i){
		if(i != pivot[i] && pivot[i] != -1){
			permutate_column[i] = pivot[i];
			permutate_column[ pivot[i] ] = i;
		}
	}

	matrix permutation_column_matrix(temp.get_col(), temp.get_col());
	permutation_column_matrix.initialize();
	permutation_column_matrix.make_all_entry_zero();
	for(int i = 0 ; i < temp.get_col() ; ++i){
		permutation_column_matrix.set_arr(i,permutate_column[i], make_entry(1,1));
	}

	temp = temp * permutation_column_matrix;


	matrix null_basis(temp.get_col() , temp.get_col() - num_pivot);
	null_basis.make_all_entry_zero();
	for(int i = 0 ; i < num_pivot ; ++i){
		for(int j = 0 ; j < null_basis.get_col() ; ++j){
			null_basis.set_arr(i,j, - temp.get_arr()[i][j + num_pivot]);
		}
	}
	for(int i = num_pivot ; i < null_basis.get_row() ; ++i){
		null_basis.set_arr(i,i - num_pivot ,make_entry(1,1));
	}

	null_basis = permutation_column_matrix * null_basis;

	return null_basis;
}

matrix matrix::
column_space(){
	matrix temp = *this;
	temp = temp.transpose();
	matrix permu = temp.permutation_matrix();
	bool independent[temp.get_row()];
	int num_independent = 0;
	for(int i = 0 ; i < temp.get_row() ; ++i) independent[i] = false;
	temp = permu * temp.eliminate();

	for(int i = 0 ; i < temp.get_row() ; ++i){
		for(int j = 0 ; j < temp.get_col() ; ++j)
			if(!temp.get_arr()[i][j].is_zero() ){
				independent[i] = true;
			}
	}

	for(int i = 0 ; i < temp.get_row() ; ++i) if(independent[i]) num_independent++;
	int idx = 0;
	temp = this->transpose();
	matrix column_space(num_independent, temp.get_col());
	for(int i = 0 ; i < temp.get_row() ; ++i){
		if(independent[i]){
			for(int j = 0 ; j < temp.get_col() ; ++j)
				column_space.set_arr(idx, j, temp.get_arr()[i][j]);	
		}
		idx++;
	}
	
	column_space = column_space.transpose();

	return column_space;
}




matrix matrix::
projection_matrix() const {
	return *(this) * (transpose() * *(this)).inverse_matrix() * transpose();
}

matrix matrix::
project(const matrix& mat) {
	if(col != 1 || row != mat.row)
		throw exception();
	return mat.projection_matrix() * *(this);
}

matrix matrix::
augumented(matrix& b){
	matrix temp(this->get_row(), this->get_col() + 1);
	temp.make_all_entry_zero();

	for(int i = 0 ; i  < temp.get_row() ; ++i){
		for(int j = 0 ; j < temp.get_col() ; ++j){
			if(j >=  this->get_col()) temp.set_arr(i,j, b.get_arr()[i][j - this->get_col()]);
			else temp.set_arr(i,j, this->get_arr()[i][j]);
		}
	}

	return temp;
}

matrix matrix::
all_solution(matrix b){
	matrix temp = this->augumented(b);
	matrix null_space = this->null_space();
	temp = temp.RREF();

	int pivot[temp.get_row()] = {0,};
	int num_pivot = 0;

	for(int i = 0 ; i < temp.get_row() ; ++i)
		for(int j = 0 ; i < j < temp.get_col() ; ++j){
			if(!temp.get_arr()[i][j].is_zero()){
				pivot[i] = j;
				break;
			}
			else
				pivot[i] = -1;
		}
	for(int i = 0 ; i < temp.get_row() ; ++i){
		if(pivot[i] == temp.get_col() -1){
			cout << "no particular solution" << endl;
			cout << "It's the closest solution" << endl;
			matrix p = b.project(*this);
			return this->all_solution(p);
		}
		else if(pivot[i] != -1) num_pivot++;
	}

	matrix particular(null_space.get_row(), 1);
	particular.make_all_entry_zero();

	for(int i = 0 ; i < num_pivot ; ++i)
		particular.set_arr(pivot[i], 0, temp.get_arr()[i][temp.get_col() - 1]);
	return particular;
}
