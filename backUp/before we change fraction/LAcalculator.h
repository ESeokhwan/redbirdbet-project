#include <iostream>
#include <vector>
#include <utility> // pair
#include <string>
#include <sstream>
using namespace std;

class matrix{
	protected:
		int row, col;
		static int permutation_count;
		vector< vector< pair<int,int> > > arr;
	public:
		matrix() : row(0), col(0) {};
		matrix (int r, int c) : row(r), col(c) {}
		matrix (const matrix& mat){row = mat.row; col = mat.col; arr = mat.arr;}


		int get_row() { return row; }
		int get_col() { return col; }
		vector< vector< pair<int, int> > > get_arr() { return arr; }
		int get_per_count() { return permutation_count;}

		void set_arr(int r, int c, pair<int,int>);
		
		void incre_perCount(){permutation_count++;}

		friend matrix operator+ (matrix& l, matrix& r);
		friend matrix operator- (matrix& l, matrix& r);
		friend matrix operator* (matrix& l, matrix& r);
		void fill();
		void initialize();
		void show();//powerup!
};

void simplify(pair<int,int>&);
pair<int,int> operator+(pair<int,int>&, pair<int,int>&);
pair<int,int> operator-(pair<int,int>&, pair<int,int>&);
pair<int,int> operator*(pair<int,int>&, pair<int,int>&);
void blank(int num);						//added for matrix.show()
int countNumberLength(const pair<int,int>&);//added for matrix.show()


int LAcalculator_main();
