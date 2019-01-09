#include "LAcalculator.h"
using namespace std;

matrix operator+ (matrix& l, matrix& r){
	if( l.row != r.row || r.col != l.col ){
		matrix temp(0,0);
		return temp;
	}
	else{
		matrix mtemp(l.row, r.col);
		for(int i = 0 ; i < l.row ; ++i){
			vector< pair<int,int> > temp;
			for(int j = 0 ; j < l.col ; ++j) temp.push_back(l.arr[i][j] + r.arr[i][j]); 
			mtemp.arr.push_back(temp);
		}
		return mtemp;
	}
}

matrix operator- (matrix& l, matrix& r){
	if( l.row != r.row || r.col != l.col ){
		matrix temp(0,0);
		return temp;
	}
	else{
		matrix mtemp(l.row,l.col);
		for(int i = 0 ; i < l.row ; ++i){
			vector< pair<int,int> > temp;
			for(int j = 0 ; j < l.col ; ++j) temp.push_back(l.arr[i][j] - r.arr[i][j]);
			mtemp.arr.push_back(temp);
		}
		return mtemp;
	}
}

matrix operator* (matrix& l, matrix& r){
	if(l.col != r.row){
		matrix temp(0,0);
		return temp;
	}
	else{
		matrix mtemp(l.row, r.col);
		for(int i = 0 ; i < l.row ; ++i){
			vector< pair<int,int> > temp;
			for(int j = 0 ; j < r.col ; ++j){
				pair<int,int> p  = make_pair(0,1);
				for(int k = 0 ; k < l.col ; ++k) {
					pair<int,int> q = l.arr[i][k]*r.arr[k][j];
					p = p + q;
				}
					temp.push_back(p);
			}
			mtemp.arr.push_back(temp);
		}
		return mtemp;
	}
}

//from here
void matrix::
set_arr (int r, int c, pair<int, int> num) {
	if(arr.size() != 0 && arr[0].size() != 0 && r < row && c < col && r >= 0 && c >= 0) arr[r][c] = num;
}
//changed

void matrix::
fill(){
	size_t idx;
	int num1,num2;
	for(int i = 0 ; i < row ; ++i){
		vector< pair<int,int> > temp;
		for(int j = 0 ; j < col ; ++j){
			string str;
			cin >> str;
			idx = str.find("/");
			
			if(idx==-1){
				istringstream iss(str);
				iss >> num1;
				temp.push_back( make_pair(num1,1) );
			}
			
			else{
				istringstream iss(str.substr(0,idx) + " " + str.substr(idx+1));
				iss >> num1 >> num2;
				pair<int,int> p = make_pair(num1,num2);
				simplify(p);
				temp.push_back( p );
			}
		}
		arr.push_back(temp);
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

void simplify(pair<int,int>& p){
	int count = 0;
	int l = p.first > 0 ? p.first : -p.first,
		r = p.second > 0 ? p.second : -p.second;
	int m = l > r ? l : r;

	if(p.first < 0 && p.first*p.second > 0){
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

void blank(int num){
    for(int i = 0 ; i < num ; ++i) cout << ' ';
}


int LAcalculator_main(){
	char op;
	int row , col;
	cin >> row >> col;
	matrix mat1(row,col);
	mat1.fill();

	cin >> row >> col;
	matrix mat2(row,col);
	mat2.fill();

	mat1.show();

	cout << endl;

	mat2.show();

	matrix matadd = mat1 + mat2;

	matrix matsub = mat1 - mat2;

	matrix matmul = mat1 * mat2;

	cout << endl;
	matadd.show();

	cout << endl;
	matsub.show();

	cout << endl;
	matmul.show();

	return 0;
}
