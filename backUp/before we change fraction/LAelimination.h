#include "LAcalculator.h"
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

matrix changes_two_rows(matrix mat, int row1, int row2);
matrix move_to_last_row(matrix mat, int row);
matrix remove_entry_matrix(matrix& mat, int substitution_row, int row, int col);
matrix eliminate(matrix mat);
matrix permutation_matrix(matrix mat);
matrix elimination_matrix(matrix mat);
int LAelimination_main();
