#include <iostream>
#include <vector>
#include <map>
#include <utility> // pair
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>
using namespace std;

int gcd(int num1, int num2);
int lcm(int num1, int num2);

class term {//base가 음수일 때 고려해야함!!
 protected :
	int base;
	int root;//몇 제곱근에서 몇
	int coefficient;

	void simplify();

 public :
	term();
	term(int _coefficient);
	term(int _root, int _base);
	term(int _coefficient, int _root, int _base);
	term(const term& _term);

	void test_show();
	
	friend term operator+(const term& termR);
	friend term operator-(const term& termR);

	friend term operator*(const int& numL, const term& termR);
	friend term operator*(const term& termL, const int& numR);

	friend term operator*(const term& termL, const term& termR);

	friend class terms;
};

class terms {
 protected :
	vector<term> arr;
	int num_of_terms;

	void simplify();

 public :
	void sort();
	terms();
	terms(const term& _term);
	terms(const terms& _terms);

	void push_back(const term& _term);
	void push_back(const int& _term);

	void test_show();

	friend terms operator+(const terms& _terms);
	friend terms operator-(const terms& _terms);

	friend terms operator+(const term& termL, const term& termR);
	friend terms operator+(const int& numL, const term& termR);
	friend terms operator+(const term& termL, const int& numR);
	friend terms operator+(const terms& termsL, const int& numR);
	friend terms operator+(const int& numL, const terms& termsR);
	friend terms operator+(const terms& termsL, const term& termR);
	friend terms operator+(const term& termL, const terms& termsR);
	friend terms operator+(const terms& termsL, const terms& termsR);

	friend terms operator-(const term& termL, const term& termR);
	friend terms operator-(const int& numL, const term& termR);
	friend terms operator-(const term& termL, const int& numR);
	friend terms operator-(const terms& termsL, const int& numR);
	friend terms operator-(const int& numL, const terms& termsR);
	friend terms operator-(const terms& termsL, const term& termR);
	friend terms operator-(const term& termL, const terms& termsR);
	friend terms operator-(const terms& termsL, const terms& termsR);

//from here
	friend terms operator*(const int& numL, const terms& termsR);
	friend terms operator*(const terms& termsL, const int& numR);
	friend terms operator*(const term& termL, const terms& termsR);
	friend terms operator*(const terms& termsL, const term& termR);
	friend terms operator*(const terms& termsL, const terms& termsR);
//to here
	
};

class fraction{//How can we treat the error devided by zero.
 protected:
	pair<int,int> fract;
	int length;
	bool isRoot1;
	bool isRoot2;

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
	friend istream& operator>>(istream& in, fraction& rhs);
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
	void normalize();

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
		
	matrix &operator= (const matrix& rhs);

	friend matrix operator+ (const matrix& l, const matrix& r);
	friend matrix operator- (const matrix& l, const matrix& r);
	friend matrix operator* (const matrix& l, const matrix& r);
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
	matrix column_space();
	matrix all_solution(matrix b);
	matrix augumented(matrix& b);
	void find_determinant();
	fraction get_determinant();

	matrix projection_matrix() const;
	matrix project(const matrix& mat);

	matrix gram_schmidt();
};
