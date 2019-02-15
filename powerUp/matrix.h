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
 friend class terms;
 friend class fraction;

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

	term& operator=(const term& r);
	term& operator=(const int& r);
	
 friend term operator+(const term& termR);
 friend term operator-(const term& termR);

 friend const term operator*(const int& numL, const term& termR);
 friend const term operator*(const term& termL, const int& numR);
 friend const term operator*(const term& termL, const term& termR);

 friend bool operator==(const term& l, const term& r);
 friend bool operator!=(const term& l, const term& r);
 friend bool operator==(const int& l, const term& r);
 friend bool operator!=(const int& l, const term& r);
 friend bool operator==(const term& l, const int& r);
 friend bool operator!=(const term& l, const int& r);
};

class terms {
 friend class fraction;

 protected :
	vector<term> arr;
	int num_of_terms;
	void clear();
	void sort();
	void simplify();

 public :
	terms();
	terms(const term& _term);
	terms(const terms& _terms);
	terms(const int& _term);

	void push_back(const term& _term);
	void push_back(const int& _term);

	void test_show();
	bool isPositive();

	terms& operator=(const terms& r);
	terms& operator=(const term& r);
	terms& operator=(const int& r);


 friend terms operator+(const terms& _terms);
 friend terms operator-(const terms& _terms);

 //term 과 term을 더하는 오퍼레이터가 없다고 하네....
 friend const terms operator+(const term& termL, const term& termR);
 friend const terms operator+(const int& numL, const term& termR);
 friend const terms operator+(const term& termL, const int& numR);
 friend const terms operator+(const terms& termsL, const int& numR);
 friend const terms operator+(const int& numL, const terms& termsR);
 friend const terms operator+(const terms& termsL, const term& termR);
 friend const terms operator+(const term& termL, const terms& termsR);
 friend const terms operator+(const terms& termsL, const terms& termsR);
 
 friend const terms operator-(const term& termL, const term& termR);
 friend const terms operator-(const int& numL, const term& termR);
 friend const terms operator-(const term& termL, const int& numR);
 friend const terms operator-(const terms& termsL, const int& numR);
 friend const terms operator-(const int& numL, const terms& termsR);
 friend const terms operator-(const terms& termsL, const term& termR);
 friend const terms operator-(const term& termL, const terms& termsR);
 friend const terms operator-(const terms& termsL, const terms& termsR);

 friend const terms operator*(const int& numL, const terms& termsR);
 friend const terms operator*(const terms& termsL, const int& numR);
 friend const terms operator*(const term& termL, const terms& termsR);
 friend const terms operator*(const terms& termsL, const term& termR);
 friend const terms operator*(const terms& termsL, const terms& termsR);

 //테스트는 안 해봄. 근데 아마 잘 될거임(==나 !=들)
 friend bool operator==(const terms& l, const terms& r);
 friend bool operator!=(const terms& l, const terms& r);
 friend bool operator==(const terms& l, const term& r);
 friend bool operator!=(const terms& l, const term& r);
 friend bool operator==(const term& l, const terms& r);
 friend bool operator!=(const term& l, const terms& r);
 friend bool operator==(const terms& l, const int& r);
 friend bool operator!=(const terms& l, const int& r);
 friend bool operator==(const int& l, const terms& r);
 friend bool operator!=(const int& l, const terms& r);

// friend ostream& operator<<(ostream& out, const terms& rhs);
// friend istream& operator>>(istream& in, terms& rhs);	
};

/*
class fraction{//How can we treat the error devided by zero.
protected:
	pair<int,int> fract;
	int length;
	bool isRoot1;
	bool isRoot2;

public:
	fraction();
	fraction(pair<int, int>);
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
*/
void blank(int num);

class fraction{//How can we treat the error devided by zero.
 protected:
	pair<terms, terms> fract;

 public :
	fraction();
	fraction(const fraction& rhs);
	fraction(const pair<terms, terms>& p);
	fraction(const terms& t1, const terms& t2);
	fraction(const terms& t1, const term& t2);
	fraction(const terms& t1, const int& t2);
	fraction(const term& t1, const terms& t2);
	fraction(const term& t1, const term& t2);
	fraction(const term& t1, const int& t2);
	fraction(const int& t1, const terms& t2);
	fraction(const int& t1, const term& t2);
	fraction(const int& t1, const int& t2);
	fraction(const terms& t);
	fraction(const term& t);
	fraction(const int& t);
	fraction(const double& r);
	fraction(const float& r);

	pair<terms, terms> getFract();
	void simplify();
	pair<int,string> fts();
	bool is_denominator_one();
	bool is_zero();
	void test_show();

	fraction& operator=(const fraction& r);
	fraction& operator=(const pair<terms, terms>& r);
	fraction& operator=(const terms& r);
	fraction& operator=(const term& r);
	fraction& operator=(const int& r);
	fraction& operator=(const double& r);
	fraction& operator=(const float& r);

 friend bool operator==(const int& l, const fraction& r);
 friend bool operator!=(const int& l, const fraction& r);
 friend bool operator==(const fraction& l, const int& r);
 friend bool operator!=(const fraction& l, const int& r);

 
 friend bool operator==(const double& l, const fraction& r);
 friend bool operator!=(const double& l, const fraction& r);
 friend bool operator==(const fraction& l, const double& r);
 friend bool operator!=(const fraction& l, const double& r);

 friend bool operator==(const float& l, const fraction& r);
 friend bool operator!=(const float& l, const fraction& r);

 friend bool operator==(const fraction& l, const float& r);
 friend bool operator!=(const fraction& l, const float& r);
 

 friend bool operator==(const pair<int, int>& l, const fraction& r);
 friend bool operator!=(const pair<int, int>& l, const fraction& r);
 friend bool operator==(const fraction& l, const pair<int, int>& r);
 friend bool operator!=(const fraction& l, const pair<int, int>& r);
  
 friend bool operator==(const fraction& l, const fraction& r);
 friend bool operator!=(const fraction& l, const fraction& r);

 friend fraction operator+(const fraction& l, const fraction& r);
 friend fraction operator-(const fraction& l, const fraction& r);
 friend fraction operator*(const fraction& l, const fraction& r);
 friend fraction operator/(const fraction& l, const fraction& r);
 friend fraction operator-(const fraction& rhs);
 friend ostream& operator<<(ostream& out, const fraction& rhs);
 friend istream& operator>>(istream& in, fraction& rhs);
};
fraction make_entry(int num1, int num2);
void fraction_output(fraction*,int,int);
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
		
	matrix& operator= (const matrix& rhs);
	
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
};
