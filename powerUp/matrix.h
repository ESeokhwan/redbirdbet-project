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
		fraction();
		fraction(pair<int, int> p);
		fraction(int num);
		fraction(int num1, int num2);
		fraction(const fraction& rhs);

		void simplify();

		void setLength();
		int getLength();
		bool is_zero();

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

		friend fraction operator+(const fraction&, const fraction&);
		friend fraction operator-(const fraction&, const fraction&);
		friend fraction operator*(const fraction&, const fraction&);
		friend fraction operator/(const fraction&, const fraction&);
		friend fraction operator-(const fraction&);
		friend ostream& operator<<(ostream& out, const fraction& rhs);
		friend istream& operator>>(istream& in, const fraction& rhs);
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

		matrix();
		matrix(int r, int c);
		matrix(const matrix& mat);
		~matrix();

		int get_row();
		int get_col();
		vector< vector<fraction> > get_arr();
		int get_permutation_count();

		void set_arr(int r, int c, fraction);
		
		void increase_permutation_count();

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
		matrix null_space();
		matrix all_solution(matrix b);
		matrix augumented(matrix& b);
		void find_determinant();
		fraction get_determinant(){return determinant;}


		matrix projection_matrix() const;
		matrix project(const matrix& mat);
};
