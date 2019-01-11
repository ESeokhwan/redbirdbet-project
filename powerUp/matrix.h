#include <iostream>
#include <vector>
#include <utility> // pair
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

void simplify(pair<int,int>&);
pair<int,int> operator+(pair<int,int>&, pair<int,int>&);
pair<int,int> operator-(pair<int,int>&, pair<int,int>&);
pair<int,int> operator*(pair<int,int>&, pair<int,int>&);

void blank(int num);
int countNumberLength(const pair<int,int>&);

class matrix{
	protected:
		int row, col;
		static int permutation_count;
		vector< vector< pair<int,int> > > arr;
//		matrix* permutation_matrix_ptr;
//		matrix* elimination_matrix_ptr;

	public :
		void initialize();
		void make_identity_matrix();
		void make_all_entry_zero();

		matrix() : row(0), col(0) {}
		matrix(int r, int c) : row(r), col(c) {
			make_identity_matrix();
		}
		matrix(const matrix& mat) {
			row = mat.row;
			col = mat.col;
			arr = mat.arr;
		}
		~matrix() {
//			delete permutation_matrix_ptr;
//			delete elimination_matrix_ptr;
		}

		int get_row() { return row; }
		int get_col() { return col; }
		vector< vector< pair<int, int> > > get_arr() { return arr; }
		int get_permutation_count() { return permutation_count; }

		void set_arr(int r, int c, pair<int,int>);
		
		void increase_permutation_count(){ permutation_count++; }
		
		matrix &operator= (const matrix &rhs) {
			row = rhs.row;
			col = rhs.col;
			arr = rhs.arr;
		}

		friend matrix operator+ (matrix& l, matrix& r);
		friend matrix operator- (matrix& l, matrix& r);
		friend matrix operator* (matrix l, matrix r);
		
		void fill();
		void show();

		matrix change_two_rows(int row1, int row2);
		matrix move_a_row_to_last_row(int row);
		matrix remove_entry(int substitution_row, int row, int col);
		matrix eliminate();
		matrix transpose();
		matrix permutation_matrix();
		matrix elimination_matrix();
};
