#include <iostream>
#include <vector>
#include <utility> // pair
#include <string>
#include <sstream>
using namespace std;

class matrix{
	private:
		int row, col;
		vector< vector< pair<int,int> > > arr;
	public:
		matrix (int r, int c) : row(r), col(c) {}
		matrix (const matrix& mat){row = mat.row; col = mat.col; arr = mat.arr;}
		friend matrix operator+ (matrix& l, matrix& r);
		friend matrix operator- (matrix& l, matrix& r);
		friend matrix operator* (matrix& l, matrix& r);
		void fill();
		void show();
};

void simplify(pair<int,int>&);
pair<int,int> operator+(pair<int,int>&, pair<int,int>&);
pair<int,int> operator-(pair<int,int>&, pair<int,int>&);
pair<int,int> operator*(pair<int,int>&, pair<int,int>&);
