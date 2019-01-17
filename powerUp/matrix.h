#include <iostream>
#include <vector>
#include <utility> // pair
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

class fraction{//How can we treat the error devided by zero.
	protected:
		pair<int,int> fract;
		int length;
	public:
		fraction() : fract(make_pair(1,1)) , length(1) {}
		fraction(pair<int,int> p){
			fract = p;
			setLength();
		}
		fraction(int num) {
			fract = make_pair(num, 1);
			setLength();
		}
		fraction(int num1, int num2){
			fract = make_pair(num1,num2);
			setLength();
		}
		fraction(const fraction& rhs){fract = rhs.fract; length = rhs.length;}

		void simplify();

		friend bool operator==(const int& numL, const fraction& fracR);
		friend bool operator!=(const int& numL, const fraction& fracR);

		friend bool operator==(const fraction& fracL, const int& numR);
		friend bool operator!=(const fraction& fracL, const int& numR);

		friend bool operator==(const double& numL, const fraction& fracR);
		friend bool operator!=(const double& numL, const fraction& fracR);

		friend bool operator==(const fraction& fracL, const double& numR);
		friend bool operator!=(const fraction& fracL, const double& numR);

		friend bool operator==(const float& numL, const fraction& fracR);
		friend bool operator!=(const float& numL, const fraction& fracR);

		friend bool operator==(const fraction& fracL, const float& numR);
		friend bool operator!=(const fraction& fracL, const float& numR);

		friend bool operator==(const pair<int, int>& pairL, const fraction& fracR);
		friend bool operator!=(const pair<int, int>& pairL, const fraction& fracR);
		friend bool operator==(const fraction& fracL, const pair<int, int>& pairR);
		friend bool operator!=(const fraction& fracL, const pair<int, int>& pairR);

		friend bool operator==(const fraction& fractL, const fraction& fractR);
		friend bool operator!=(const fraction& fractL, const fraction& fractR);

		friend fraction operator+(fraction&, fraction&);
		friend fraction operator-(fraction&, fraction&);
		friend fraction operator*(const fraction&, const fraction&);
		friend fraction operator/(fraction&, fraction&);
		friend fraction operator-(fraction&);//
		friend ostream& operator<<(ostream& out, fraction& rhs);
		friend istream& operator>>(istream& in, fraction& rhs);
		void setLength();
		int getLength() {return length;}
		bool is_zero(){return fract.first == 0;}
};
void blank(int num);
fraction make_entry(int num1, int num2);

class matrix{
	protected:
		int row, col;
		static int permutation_count;
		vector< vector<fraction> > arr;
		fraction determinant;
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
		vector< vector<fraction> > get_arr() { return arr; }
		int get_permutation_count() { return permutation_count; }

		void set_arr(int r, int c, fraction);
		
		void increase_permutation_count(){ permutation_count++; }
		
		matrix &operator= (const matrix& rhs) {
			row = rhs.row;
			col = rhs.col;
			arr = rhs.arr;
		}

		friend matrix operator+ (matrix& l, matrix& r);
		friend matrix operator- (matrix& l, matrix& r);
		friend matrix operator* (matrix l, matrix r);
		friend matrix operator* (const fraction& fracL, const matrix& matR);
		friend matrix operator* (const matrix& matL, const fraction& fracR);
		friend matrix operator* (const int& intL, const matrix& matR);
		friend matrix operator* (const matrix& matL, const int& intR);
		friend bool operator== (const matrix& matL, const matrix& matR);
		friend bool operator!= (const matrix& matL, const matrix& matR);
		friend fraction dotproduct(const matrix& matL, const matrix& matR);
		
		void fill();
		void show(bool no_paranthesis = false);
		void matrix_simplification();

		matrix change_two_rows(int row1, int row2);
		matrix move_a_row_to_last_row(int row);
		matrix remove_entry(int substitution_row, int row, int col);
		matrix eliminate();
		matrix transpose() const;
		matrix permutation_matrix();
		matrix elimination_matrix();

		bool LDUfactorization();

		matrix inverse_matrix();
		matrix RREF();
		matrix all_solution();
		void find_determinant();
		fraction get_determinant(){return determinant;}
};
