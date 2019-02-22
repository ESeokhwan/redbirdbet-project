#include "matrix.h"
using namespace std;

int matrix::permutation_count = 0;

int gcd(int num1, int num2)
{
	if(num1 < 0  && num2 < 0)
		throw "error occurs in 'gcd(int num1, int num2)'.\nnum1 and num2 must be positive.";
	if(num1 == 0 || num2 == 0)
		return 1;

	int tmp;
	while (num2 != 0)
	{
		tmp = num1 % num2;
		num1 = num2;
		num2 = tmp;
	}
	return num1;
}

int lcm(int num1, int num2)
{
	if(num1 <= 0 && num2 <= 0) {
		throw "error occurs in 'lcm(int num1, int num2).\nnum1 and num2 must be positive.";
	}


	return num1 * num2 / gcd(num1, num2);
}

term::
term() : base(1), root(1), coefficient(0) { }

term::
term(int _coefficient) : term() {
	coefficient = _coefficient;
}

term::
term(int _root, int _base) : term(1) {
	if(_root <= 0) {
		throw "error occurs in 'term::term(int _base, int _root)'.\nterm::root must be positive.";
	}
	if(_base == 0) {
		coefficient = 0;
		base = 1;
		root = 1;
	}
	else {
		base = _base;
		root = _root;
	}
}

term::
term(int _coefficient, int _root, int _base) : term(_root, _base) {
	coefficient = _coefficient;
}

term::
term(const term& _term) : term(_term.coefficient, _term.root, _term.base) { }

void term::
simplify() {
	if(root <= 0)
		throw "error occurs in 'term::simplify()'.\nterm::root must be positive.";
	map<int, int> factors;
	if(base == 0 || coefficient == 0) {
		root = 1;
		base = 1;
		coefficient = 0;
	}
	int tmp = base;
	for(int i = 2; i <= tmp; i++) {
		if(tmp % i == 0) {
			factors.insert(make_pair(i, 1));
			tmp /= i;
		}
		while(tmp % i == 0) {
			tmp /= i;
			factors[i]++;
		}
	}
	for(map<int, int>::iterator it = factors.begin(); it != factors.end(); it++) {
		while(it -> second >= root) {
			coefficient *= (it -> first);
			base /= int(pow(double(it -> first), double(root)));
			it -> second -= root;
		}
	}

	if(base == 1)
		root = 1;

	else {
		int gcd_ = root;
		for(map<int, int>::iterator it = factors.begin(); it != factors.end(); it++) {
			if(it -> second != 0)
				gcd_ = gcd(gcd_, it -> second);
		}
		root /= gcd_;
		base = int(pow(double(base), double(1)/double(gcd_)));
	}
}

void term::
test_show() {
	cout << "coefficient : " << coefficient << endl;
	cout << "root : " << root << endl;
	cout << "base : " << base << endl;
	cout << endl;
}

term& term::
operator=(const term& r) {
	coefficient = r.coefficient;
	root = r.root;
	base = r.base;

	return *(this);
}

term& term::
operator=(const int& r) {
	term tmp(r);
	return *(this) = tmp;
}


term operator+(const term& termR) {
	return termR;
}


term operator-(const term& termR) {
	term result(termR);
	result.coefficient *= -1;
	return result;
}


const term operator*(const int& numL, const term& termR) {
	term result(termR);
	result.coefficient = termR.coefficient * numL;
	result.simplify();

	return result;
}

const term operator*(const term& termL, const int& numR) {
	term result;
	result = numR * termL;
	result.simplify();
	return result;
}

const term operator*(const term& termL, const term& termR) {
	term result;
	result.coefficient = termL.coefficient * termR.coefficient;

	result.root = lcm(termL.root, termR.root);

	result.base = int(
			pow(double(termL.base), double(result.root/termL.root)) *
			pow(double(termR.base), double(result.root/termR.root)));

	result.simplify();

	return result;
}

bool operator==(const term& l, const term& r) {
	term tmp1, tmp2;
	tmp1 = l;
	tmp2 = r;
	tmp1.simplify();
	tmp2.simplify();
	if(tmp1.coefficient == tmp2.coefficient && tmp1.root == tmp2.root && tmp1.base == tmp2.base)
		return true;
	return false;
}

bool operator!=(const term& l, const term& r) {
	return !(l == r);
}

bool operator==(const int& l, const term& r) {
	term tmp(l);
	return (tmp == r);
}

bool operator!=(const int& l, const term& r) {
	return !(l == r);
}

bool operator==(const term& l, const int& r) {
	return (r == l);
}

bool operator!=(const term& l, const int& r) {
	return !(l == r);
}

terms::
terms() : num_of_terms(0) {
	this -> push_back(0);
}

terms::
terms(const term& _term) : terms() {
	this -> push_back(_term);
}

terms::
terms(const int& num) : terms() {
	term _term = num;
	this -> push_back(_term);
}

terms::
terms(const terms& _terms) : terms() {
	for(int i = 0; i < _terms.num_of_terms; i++)
		this -> push_back(_terms.arr[i]);
}

void terms::
push_back(const term& _term) {
	arr.push_back(_term);
	num_of_terms++;
	simplify();
}

void terms::
push_back(const int& num) {
	term input(num);
	this -> push_back(input);
}

bool terms::
isPositive(){
	double sum = 0;
	for(int i = 0 ; i < num_of_terms ; ++i) sum += arr[i].coefficient * pow( arr[i].base, arr[i].root);
	return sum > 0;
}

void terms::
test_show() {
	simplify();
	for(int i = 0; i < num_of_terms; i++) 
		arr[i].test_show();
}

void terms::
clear() {
	num_of_terms = 0;
	arr.clear();
}

void terms::
sort() {
	bool change = true;
	term tmp;
	while(change) {
		change = false;
		for(int i = 0; i < num_of_terms - 1; i++) {
			if(arr[i].root > arr[i+1].root) {
				tmp = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = tmp;
				change = true;
			}
		}
	}
	change = true;
	while(change) {
		change = false;
		for(int i = 0; i < num_of_terms - 1; i++) {
			if(arr[i].root == arr[i+1].root) {
				if(arr[i].base > arr[i+1].base) {
					tmp = arr[i];
					arr[i] = arr[i+1];
					arr[i+1] = tmp;
					change = true;
				}
			}
		}
	}
}

void terms::
simplify() {
	for(int i = 0; i < num_of_terms; i++) {
		arr[i].simplify();
	}

	sort();

	for(int i = 0; i < num_of_terms - 1; i++) {
		if(arr[i].root == 1) {
			while(arr[i+1].root == 1) {
				arr[i].coefficient = arr[i].coefficient +
					arr[i+1].coefficient;

				vector<term>::iterator it = arr.begin();

				arr.erase(it + i + 1);
				--num_of_terms;

				if(it + i + 1 == arr.end())
					break;
			}
		}
		else {
			while(arr[i].root == arr[i+1].root &&
					arr[i].base == arr[i+1].base) {
				arr[i].coefficient = arr[i].coefficient +
					arr[i+1].coefficient;

				vector<term>:: iterator it = arr.begin();

				arr.erase(it + i + 1);
				--num_of_terms;

				if(it + i + 1 == arr.end())
					break;
			}
		}
	}
	if(num_of_terms == 0) 
		arr.push_back(term());
	if(num_of_terms != 1) {
		for(int i = 0; i < num_of_terms ; i++) {
			if(arr[i] == 0) {
				vector<term>:: iterator it = arr.begin();
				arr.erase(it + i);
				--num_of_terms;
			}
		}
	}
}

terms& terms::
operator=(const terms& r) {
	clear();
	for(int i = 0; i < r.num_of_terms; i++)
		push_back(r.arr[i]);
	return *(this);
}

terms& terms::
operator=(const term& r) {
	terms tmp(r);
	return *(this) = tmp;
}

terms& terms::
operator=(const int& r) {
	terms tmp(r);
	return *(this) = tmp;
}

terms operator+(const terms& _terms) {
	return _terms;
}


terms operator-(const terms& _terms) {
	terms result(_terms);
//	cout << _terms.num_of_terms<< endl;
	for(int i = 0; i < _terms.num_of_terms; i++) {
//		result.arr[i].test_show();
		result.arr[i] = -1 * result.arr[i];
	}
	return result;
}

const terms operator+(const term& termL, const term& termR) {
	terms result;
	result.arr.push_back(termL);
	result.arr.push_back(termR);

	result.simplify();

	return result;
}

const terms operator+(const int& numL, const term& termR) {
	term tmp(numL);
	terms result;

	result = tmp + termR;
	result.simplify();

	return result;
}

const terms operator+(const term& termL, const int& numR) {
	terms result;
	result = numR + termL;
	result.simplify();

	return result;
}

const terms operator+(const terms& termsL, const int& numR){
	terms temp(termsL);
	temp.push_back(numR);
	temp.simplify();
	return temp;
}

const terms operator+(const int& numL, const terms& termsR){
	terms temp(termsR);
	temp.push_back(numL);
	temp.simplify();
	return temp;
}

const terms operator+(const terms& termsL, const term& termR){
	terms temp(termsL);
	temp.push_back(termR);

	temp.simplify();
	return temp;
}

const terms operator+(const term& termL, const terms& termsR){
	terms temp(termsR);
	temp.push_back(termL);

	temp.simplify();
	return temp;
}


const terms operator+(const terms& termsL, const terms& termsR){
	terms temp(termsL);
	for(int i = 0 ; i < termsR.num_of_terms ; ++i)
		temp.push_back(termsR.arr[i]);

	temp.simplify();
	return temp;
}

const terms operator-(const term& termL, const term& termR) {
	terms temp;
	temp = termL + -termR;
	temp.simplify();

	return temp;
}

const terms operator-(const int& numL, const term& termR) {
	terms temp;
	temp = numL + -termR;
	temp.simplify();

	return temp;
}

const terms operator-(const terms& termsL, const int& numR){
	terms temp;
	temp = termsL + -numR;
	temp.simplify();

	return temp;
}

const terms operator-(const int& numL, const terms& termsR){
	terms temp;
	temp = numL + -termsR;
	temp.simplify();

	return temp;
}

const terms operator-(const terms& termsL, const term& termR){
	terms temp;
	temp = termsL + -termR;
	temp.simplify();

	return temp;
}

const terms operator-(const term& termL, const terms& termsR){
	terms temp;
	temp = termL + -termsR;
	temp.simplify();

	return temp;
}

const terms operator-(const terms& termsL, const terms& termsR){
	terms temp(termsL);
	for(int i = 0 ; i < termsR.num_of_terms ; ++i)
		temp.push_back(-termsR.arr[i]);
	temp.simplify();
	return temp;
}

const terms operator*(const term& termL, const terms& termsR){
	terms temp(termsR);
	for(int i = 0 ; i < temp.num_of_terms ; ++i) temp.arr[i] = temp.arr[i] * termL;
	temp.simplify();
	return temp;
}

const terms operator*(const terms& termsL, const term& termR){
	terms temp(termsL);
	for(int i = 0 ; i < temp.num_of_terms ; ++i) temp.arr[i] = temp.arr[i] * termR;
	temp.simplify();
	return temp;
}

const terms operator*(const terms& termsL, const terms& termsR){
	terms temp;
	for(int i = 0 ; i < termsL.num_of_terms ; ++i){
		for(int j = 0 ; j < termsR.num_of_terms ; ++j){
			term temp_term = termsL.arr[i] * termsR.arr[j];
			temp.push_back(temp_term);
		}
	}
	temp.simplify();
	return temp;
}

const terms operator*(const int& numL, const terms& termsR) {
	terms result(termsR);
	for(int i = 0; i < termsR.arr.size(); i++)
		result.arr[i] = numL * result.arr[i];
	result.simplify();
	return result;
}

const terms operator*(const terms& termsL, const int& numR) {
	terms result;
	result = numR * termsL;
	result.simplify();
	return result;
}

bool operator==(const terms& l, const terms& r) {
	terms tmp1(l), tmp2(r);
	tmp1.simplify();
	tmp2.simplify();
	if(tmp1.num_of_terms == tmp2.num_of_terms) {
		for(int i = 0; i < tmp1.num_of_terms; i++) {
			if(tmp1.arr[i] != tmp2.arr[i])
				return false;
		}
		return true;
	}
	return false;
}

bool operator!=(const terms& l, const terms& r) {
	return !(l == r);
}

bool operator==(const terms& l, const term& r) {
	terms tmp(r);
	return (l == tmp);
}

bool operator!=(const terms& l, const term& r) {
	return !(l == r);
}

bool operator==(const term& l, const terms& r) {
	terms tmp(l);
	return (tmp == r);
}

bool operator!=(const term& l, const terms& r) {
	return !(l == r);
}

bool operator==(const terms& l, const int& r) {
	terms tmp(r);
	return (l == tmp);
}

bool operator!=(const terms& l, const int& r) {
	return !(l == r);
}

bool operator==(const int& l, const terms& r) {
	terms tmp(l);
	return (tmp == r);
}

bool operator!=(const int& l, const terms& r) {
	return !(l == r);
}

fraction make_entry(int num1, int num2){
    fraction result(num1, num2); 
    return result;
}

void blank(int num){
	for(int i = 0 ; i < num ; ++i) cout << ' ';
}

fraction::
fraction() {
	terms t1 = 0, t2 = 1;
	fract.first = t1, fract.second = t2;
	value = 0.0;
}

fraction::
fraction(const fraction& rhs) : fract(rhs.fract), value(rhs.value) {}

fraction::
fraction(const pair<terms,terms>& p) : fract(p) {
	double son = 0.0;
	double mom = 0.0;
	for(int i = 0; i < fract.first.num_of_terms; i++) {
		son += double(fract.first.arr[i].coefficient) * pow(double(fract.first.arr[i].base), 1.0 / double(fract.first.arr[i].root));
	}
	for(int i = 0; i < fract.second.num_of_terms; i++) {
		mom += double(fract.second.arr[i].coefficient) * pow(double(fract.second.arr[i].base), 1.0 / double(fract.second.arr[i].root));
	}
	value = son/mom;
}

fraction::
fraction(const int& t) {
	terms terms1 = t, terms2 = 1;
	fract.first = terms1;
	fract.second = terms2;
	double son = 0.0;
	double mom = 0.0;
	for(int i = 0; i < fract.first.num_of_terms; i++) {
		son += double(fract.first.arr[i].coefficient) * pow(double(fract.first.arr[i].base), 1.0 / double(fract.first.arr[i].root));
	}
	for(int i = 0; i < fract.second.num_of_terms; i++) {
		mom += double(fract.second.arr[i].coefficient) * pow(double(fract.second.arr[i].base), 1.0 / double(fract.second.arr[i].root));
	}
	value = son/mom;
}

fraction::
fraction(const term& t) {
	terms terms1 = t, terms2 = 1;
	fract.first = terms1, fract.second = terms2;
	double son = 0.0;
	double mom = 0.0;
	for(int i = 0; i < fract.first.num_of_terms; i++) {
		son += double(fract.first.arr[i].coefficient) * pow(double(fract.first.arr[i].base), 1.0 / double(fract.first.arr[i].root));
	}
	for(int i = 0; i < fract.second.num_of_terms; i++) {
		mom += double(fract.second.arr[i].coefficient) * pow(double(fract.second.arr[i].base), 1.0 / double(fract.second.arr[i].root));
	}
	value = son/mom;
}

fraction::
fraction(const terms& t) {
	terms terms1 = t, terms2 = 1;
	fract.first = terms1, fract.second = terms2;
	double son = 0.0;
	double mom = 0.0;
	for(int i = 0; i < fract.first.num_of_terms; i++) {
		son += double(fract.first.arr[i].coefficient) * pow(double(fract.first.arr[i].base), 1.0 / double(fract.first.arr[i].root));
	}
	for(int i = 0; i < fract.second.num_of_terms; i++) {
		mom += double(fract.second.arr[i].coefficient) * pow(double(fract.second.arr[i].base), 1.0 / double(fract.second.arr[i].root));
	}
	value = son/mom;
}

fraction::
fraction(const int& t1, const int& t2){
	terms terms1 = t1, terms2 = t2;
	fract.first = terms1, fract.second = terms2;
	double son = 0.0;
	double mom = 0.0;
	for(int i = 0; i < fract.first.num_of_terms; i++) {
		son += double(fract.first.arr[i].coefficient) * pow(double(fract.first.arr[i].base), 1.0 / double(fract.first.arr[i].root));
	}
	for(int i = 0; i < fract.second.num_of_terms; i++) {
		mom += double(fract.second.arr[i].coefficient) * pow(double(fract.second.arr[i].base), 1.0 / double(fract.second.arr[i].root));
	}
	value = son/mom;
}

fraction::
fraction(const int& t1, const term& t2){
	terms terms1 = t1, terms2 = t2;
	fract.first = terms1;
	fract.second = terms2;
	double son = 0.0;
	double mom = 0.0;
	for(int i = 0; i < fract.first.num_of_terms; i++) {
		son += double(fract.first.arr[i].coefficient) * pow(double(fract.first.arr[i].base), 1.0 / double(fract.first.arr[i].root));
	}
	for(int i = 0; i < fract.second.num_of_terms; i++) {
		mom += double(fract.second.arr[i].coefficient) * pow(double(fract.second.arr[i].base), 1.0 / double(fract.second.arr[i].root));
	}
	value = son/mom;
}

fraction::
fraction(const int& t1, const terms& t2){
	terms terms1 = t1, terms2 = t2;
	fract.first = terms1, fract.second = terms2;
	double son = 0.0;
	double mom = 0.0;
	for(int i = 0; i < fract.first.num_of_terms; i++) {
		son += double(fract.first.arr[i].coefficient) * pow(double(fract.first.arr[i].base), 1.0 / double(fract.first.arr[i].root));
	}
	for(int i = 0; i < fract.second.num_of_terms; i++) {
		mom += double(fract.second.arr[i].coefficient) * pow(double(fract.second.arr[i].base), 1.0 / double(fract.second.arr[i].root));
	}
	value = son/mom;
}

fraction::
fraction(const term& t1, const int& t2){
	terms terms1 = t1, terms2 = t2;
	fract.first = terms1, fract.second = terms2;
	double son = 0.0;
	double mom = 0.0;
	for(int i = 0; i < fract.first.num_of_terms; i++) {
		son += double(fract.first.arr[i].coefficient) * pow(double(fract.first.arr[i].base), 1.0 / double(fract.first.arr[i].root));
	}
	for(int i = 0; i < fract.second.num_of_terms; i++) {
		mom += double(fract.second.arr[i].coefficient) * pow(double(fract.second.arr[i].base), 1.0 / double(fract.second.arr[i].root));
	}
	value = son/mom;
}

fraction::
fraction(const term& t1, const term& t2){
	terms terms1 = t1, terms2 = t2;
	fract.first = terms1, fract.second = terms2;
	double son = 0.0;
	double mom = 0.0;
	for(int i = 0; i < fract.first.num_of_terms; i++) {
		son += double(fract.first.arr[i].coefficient) * pow(double(fract.first.arr[i].base), 1.0 / double(fract.first.arr[i].root));
	}
	for(int i = 0; i < fract.second.num_of_terms; i++) {
		mom += double(fract.second.arr[i].coefficient) * pow(double(fract.second.arr[i].base), 1.0 / double(fract.second.arr[i].root));
	}
	value = son/mom;
}

fraction::
fraction(const term& t1, const terms& t2){
	terms terms1 = t1, terms2 = t2;
	fract.first = terms1, fract.second = terms2;
	double son = 0.0;
	double mom = 0.0;
	for(int i = 0; i < fract.first.num_of_terms; i++) {
		son += double(fract.first.arr[i].coefficient) * pow(double(fract.first.arr[i].base), 1.0 / double(fract.first.arr[i].root));
	}
	for(int i = 0; i < fract.second.num_of_terms; i++) {
		mom += double(fract.second.arr[i].coefficient) * pow(double(fract.second.arr[i].base), 1.0 / double(fract.second.arr[i].root));
	}
	value = son/mom;
}

fraction::
fraction(const terms& t1, const int& t2){
	terms terms1 = t1, terms2 = t2;
	fract.first = terms1, fract.second = terms2;
	double son = 0.0;
	double mom = 0.0;
	for(int i = 0; i < fract.first.num_of_terms; i++) {
		son += double(fract.first.arr[i].coefficient) * pow(double(fract.first.arr[i].base), 1.0 / double(fract.first.arr[i].root));
	}
	for(int i = 0; i < fract.second.num_of_terms; i++) {
		mom += double(fract.second.arr[i].coefficient) * pow(double(fract.second.arr[i].base), 1.0 / double(fract.second.arr[i].root));
	}
	value = son/mom;
}

fraction::
fraction(const terms& t1, const term& t2){
	terms terms1 = t1, terms2 = t2;
	fract.first = terms1, fract.second = terms2;
	double son = 0.0;
	double mom = 0.0;
	for(int i = 0; i < fract.first.num_of_terms; i++) {
		son += double(fract.first.arr[i].coefficient) * pow(double(fract.first.arr[i].base), 1.0 / double(fract.first.arr[i].root));
	}
	for(int i = 0; i < fract.second.num_of_terms; i++) {
		mom += double(fract.second.arr[i].coefficient) * pow(double(fract.second.arr[i].base), 1.0 / double(fract.second.arr[i].root));
	}
	value = son/mom;
}

fraction::
fraction(const terms& t1, const terms& t2) {
	fract.first = t1, fract.second = t2;
	cout << "hey ";
	cout << *this << endl;
	double son = 0.0;
	double mom = 0.0;
	for(int i = 0; i < fract.first.num_of_terms; i++) {
		son += double(fract.first.arr[i].coefficient) * pow(double(fract.first.arr[i].base), 1.0 / double(fract.first.arr[i].root));
	}
	for(int i = 0; i < fract.second.num_of_terms; i++) {
		mom += double(fract.second.arr[i].coefficient) * pow(double(fract.second.arr[i].base), 1.0 / double(fract.second.arr[i].root));
	}
	value = son/mom;
}

fraction::
fraction(const double& r) {
	double denominator = 1.0;
	while(double(int(r * denominator)) != r * denominator)
		denominator *= 10.0;
	fract.first = int(r * denominator);
	fract.second = int(denominator);
	simplify();
	value = double(r);
}

fraction::
fraction(const float& r) {
	float denominator = 1.0;
	while(float(int(r * denominator)) != r * denominator)
		denominator *= 10.0;
	fract.first = int(r * denominator);
	fract.second = int(denominator);
	simplify();
	value = float(r);
}

pair<terms, terms> fraction::
getFract() {
	return fract;
}

double fraction::
getValue() const {
	return value;
}
void fraction::
rationalize() {
	if(fract.second.num_of_terms == 1) {
		term tmp(1, fract.second.arr[0].root, fract.second.arr[0].base);
		for(int i = 0; i < fract.second.arr[0].root - 1; i++) {
			fract.first = fract.first * tmp;
			fract.second = fract.second * tmp;
		}
	}
	else if(fract.second.num_of_terms == 2) {
		if(fract.second.arr[0].root < 3 && fract.second.arr[1].root < 3) {
			terms ts_tmp;
			ts_tmp = fract.second.arr[0] - fract.second.arr[1];
			fract.first = fract.first * ts_tmp;
			fract.second = fract.second * ts_tmp;
		}
	}
}


//to do
void fraction::
simplify_without_rationalize(){
	if(fract.second == 0) {
		fract.first = 1;
		return;
	}
	else if(fract.first == 0) {
		fract.second = 1;
		return;
	}
	vector<int> v;
	int gcd_of_coefficients[2];
	terms temp[2] = {fract.first, fract.second};
	temp[0].simplify();
	temp[1].simplify();
	terms abandoned_terms[2] = {temp[0], temp[1]};
	terms one = 1;
	int common_factor = 1, coef_min = -1, temp_int = 0, i = 0, j = 0;// min의 초기값을 -1로 바꿈
	bool neg = temp[1].arr[0].coefficient < 0;

	for(i = 0 ; i < 2 ; ++i)
		for(j = 0 ; j < temp[i].num_of_terms ; ++j){
			temp_int = temp[i].arr[j].coefficient;
			if(temp_int < 0) temp_int = -temp_int;
			v.push_back(temp_int);
		}
	coef_min = *min_element(v.begin(), v.end());

	for(i = coef_min ; i > 1 ; --i){
		for(j = 0 ; j < v.size() ; ++j)
			if(v[j]%i!=0) break;
		if(j == v.size()){
			common_factor = i;
			break;
		}
	}

	if(neg)
		common_factor = -common_factor;
	for(i = 0 ; i < 2 ; ++i)
		for(j = 0 ; j < temp[i].num_of_terms ; ++j)
			temp[i].arr[j].coefficient /= common_factor;

	fract = make_pair(temp[0], temp[1]);

	for(i = 0; i < 2; i++) {
		gcd_of_coefficients[i] = abandoned_terms[i].arr[0].coefficient;
		for(j = 0; j < abandoned_terms[i].num_of_terms; j++) {
			gcd_of_coefficients[i] = gcd(gcd_of_coefficients[i], abs(abandoned_terms[i].arr[j].coefficient));
		}
		for(j = 0; j < abandoned_terms[i].num_of_terms; j++) {
			abandoned_terms[i].arr[j].coefficient /= gcd_of_coefficients[i];
		}
	}
	//여기까지는 정수 게수만 처리한 것임
	
	temp[0] = fract.first;
	temp[1] = fract.second;
	int gcd_of_roots_arr[2];
	int gcd_of_roots = temp[0].arr[0].root;
	int I_need_this[2];
	vector< map<int, pair<int, int> > > factors[2];
	vector< int > cofactors[2]; //fract.fist와 second 각각의 공통 factor
	vector<int> cofactors_deleted; //분모와 분자의 공통 factor
	for(i = 0; i < 2; i++) {
//		cout << "start" << i << endl;
		vector<int> tmpcofactors;
		//뒤에는 fraction의 terms들에 첫번째 term의 factor를 담는 과정이다.
		int tmp = temp[i].arr[0].base;
		gcd_of_roots_arr[i] = temp[i].arr[0].root;
		for(j = 2; j <= temp[i].arr[0].base; j++) {
			if(tmp % j == 0) {
				tmp /= j;
				tmpcofactors.push_back(j);
			}
			while(tmp % j == 0) {
				tmp /= j;
			}
		}

		//뒤에는 fraction의 terms들의 term들이 공통으로 갖고 조건에 맞는 factor들만 남기는 과정이다.
		for(j = 0; j < temp[i].num_of_terms; j++) {
			gcd_of_roots_arr[i] = gcd(gcd_of_roots_arr[i], temp[i].arr[j].root);
			gcd_of_roots = gcd(gcd_of_roots, temp[i].arr[j].root);
		}
		for(j = 0; j < temp[i].num_of_terms;j++) {
			tmp = temp[i].arr[j].base;
			for(vector<int>::iterator it = tmpcofactors.begin(); it < tmpcofactors.end(); it++) {
				int num_of_power = 0;
				if(tmp % *it != 0) {
					tmpcofactors.erase(it);
				}
				while(tmp % *(it) == 0) {
					tmp /= *(it);
					num_of_power++;
				}
				if(gcd_of_roots_arr[i] * num_of_power < temp[i].arr[j].root && num_of_power != 0) {
					tmpcofactors.erase(it);
				}
			}
		}
//		cout << "여긴 왔니?" << endl;
		cofactors[i] = tmpcofactors;
//		cout << "check" << endl;

		//뒤의 과정은 fraction의 terms들의 term들의 공통 factor와 그 factor가 몇번 곱해지는지 저장하는 과정이다.
		for(j = 0; j < temp[i].num_of_terms;j++) {
			tmp = temp[i].arr[j].base;
			map<int, pair< int, int > > tmpfactors; //<인수, < 곱해진 횟수, 몇제곱근의 base에 대한 거인지>>
			for(vector<int>::iterator it = cofactors[i].begin(); it != cofactors[i].end(); it++) {
				tmpfactors.insert(make_pair(*(it), make_pair(1, temp[i].arr[j].root)));
				tmp /= *(it);
//				cout << "여긴??" <<endl;
				while(tmp % *(it) == 0) {
					tmp /= *(it);
					tmpfactors[*(it)].first++;
				}
			}
			factors[i].push_back(tmpfactors);
		}

		double root_min = -1;
		for(vector<int>::iterator it = cofactors[i].begin(); it < cofactors[i].end(); it++) {
			for(j = 0; j < temp[i].num_of_terms;j++) {
				if(root_min == -1) {
					root_min = double(factors[i][j][*(it)].first)/double(factors[i][j][*(it)].second);
				}
				root_min = min(root_min, double(factors[i][j][*(it)].first)/double(factors[i][j][*(it)].second));
			}
		}
		for(j = 1; double(j)/double(gcd_of_roots_arr[i]) <= root_min; j++) { }
		int exponent_of_delete = j - 1;
		I_need_this[i] = exponent_of_delete;

		for(vector<int>::iterator it = cofactors[i].begin(); it < cofactors[i].end(); it++) {
			for(j = 0; j < abandoned_terms[i].num_of_terms;j++) {
				int root_per_gcd = abandoned_terms[i].arr[j].root / gcd_of_roots_arr[i];
				for(int k = 0; k < exponent_of_delete * root_per_gcd; k++) {
					abandoned_terms[i].arr[j].base /= *(it);
				}
			}
		}
		abandoned_terms[i].simplify();
	}
	if(abandoned_terms[0] == abandoned_terms[1] && abandoned_terms[0] != 1) {
		for(i = 0; i < 2; i++) {
			temp[i] = 1;
			for(vector<int>::iterator it = cofactors[i].begin(); it < cofactors[i].end(); it++) {
				temp[i] = temp[i] * term(1, gcd_of_roots_arr[i], int(pow(double(*(it)), double(I_need_this[i]))));
			}
			temp[i] = temp[i] * gcd_of_coefficients[i];
		}
		fract = make_pair(temp[0], temp[1]);
		fract.first.simplify();
		fract.second.simplify();
		simplify();
	}	

//	cout << "Hey?" << endl;
	for(i = 0; i < cofactors[0].size(); i++) {
		for(vector<int>::iterator it = cofactors[1].begin(); it < cofactors[1].end(); it++) {
			if(cofactors[0][i] == *(it)) {
				cofactors_deleted.push_back(*(it));
				cofactors[1].erase(it);
			}
		}
	}
//	cout << "excuse me?" << endl;
	double root_min = -1;
	for(vector<int>::iterator it = cofactors_deleted.begin(); it < cofactors_deleted.end(); it++) {
		for(i = 0; i < 2; i++) {
			for(j = 0; j < temp[i].num_of_terms;j++) {
				if(root_min == -1) {
					root_min = double(factors[i][j][*(it)].first)/double(factors[i][j][*(it)].second);
				}
				root_min = min(root_min, double(factors[i][j][*(it)].first)/double(factors[i][j][*(it)].second));
			}
		}
	}
	for(i = 1; double(i)/double(gcd_of_roots) <= root_min; i++) { }
	int exponent_of_delete = i - 1;
	
	for(vector<int>::iterator it =  cofactors_deleted.begin(); it < cofactors_deleted.end(); it++) {
		for(i = 0; i < 2; i++) {
			for(j = 0; j < temp[i].num_of_terms;j++) {
				int root_per_gcd = temp[i].arr[j].root / gcd_of_roots;
				for(int k = 0; k < exponent_of_delete * root_per_gcd; k++) {
					temp[i].arr[j].base /= *(it);
				}
			}
		}
	}
	fract = make_pair(temp[0], temp[1]);
	fract.first.simplify();
	fract.second.simplify();
}

void fraction::
simplify() {
	simplify_without_rationalize();
	rationalize();
	simplify_without_rationalize();
}

//fraction을 조작하여 string과 int pair를 return하는 함수
pair<int,string> fraction::
fts() const {
	int stack = 0, loop = 1;
	bool is_neg = true, multi_term = false;
	string str = "";
	terms _terms[2] = { fract.first, fract.second };
/*
	if(is_zero()){
		str = "0";
		return make_pair(1, str);
	}
*/
	if(!is_denominator_one()) 
		loop++;

	for(int i = 0 ; i < loop ; ++i){
		for(int j = 0 ; j < _terms[i].num_of_terms ; ++j){
			term temp = _terms[i].arr[j];
			is_neg = (temp.coefficient < 0);
			multi_term = ( j > 0 );
			if(is_neg) temp.coefficient = -temp.coefficient;
			
			
			if(multi_term) {
				if(!is_neg)
					str = str + "+";
				else
					str = str + "-";
			}
			else
				if(is_neg)
					str = str + "-";

			switch(temp.root) {
				case 1 :str = str + to_string(temp.coefficient); break;
				case 2 :if(temp.coefficient != 1) str = str + to_string(temp.coefficient);
						str = str + "√" + to_string(temp.base); stack++; break;
				case 3 :if(temp.coefficient != 1) str = str + to_string(temp.coefficient);
						str = str + "∛" + to_string(temp.base); stack++; break;
				case 4 :if(temp.coefficient != 1) str = str + to_string(temp.coefficient);
						str = str + "∜" + to_string(temp.base); stack++; break;
				default:if(temp.coefficient != 1) str = str + to_string(temp.coefficient);
						str = str + "r" + to_string(temp.root) + "v" + to_string(temp.base); break;
			}
		}
		if(loop == 2 && i == 0) str = str + "/";
	}	
	return make_pair(str.length() - 2*stack, str);
}

bool fraction::
is_denominator_one() const {
	fraction tmp(*this);
	tmp.simplify();
	return (tmp.fract.second.num_of_terms == 1) && (tmp.fract.second.arr[0].coefficient == 1 && tmp.fract.second.arr[0].base == 1);
}

bool fraction::
is_denominator_zero() const {
	fraction tmp(*this);
	tmp.simplify();
	return (tmp.fract.second.num_of_terms == 1) && (tmp.fract.second.arr[0].coefficient == 0);
}

bool fraction::
is_zero() const {
	fraction tmp(*this);
	tmp.simplify();
	return (tmp.fract.first.num_of_terms == 1 && tmp.fract.first.arr[0].coefficient == 0);
}


fraction fraction::
power(int exponent) {
	if(exponent > 100)
		throw "error occurs on 'fraction::power(int exponent)'. Your computer can be damaged";
	fraction tmp(*this);
	fraction result(*this);
	tmp.simplify();
	result.simplify();
	for(int i = 0; i < exponent - 1; i++)
		result = result * tmp;
	return result;
}

fraction fraction::
root(int exponent) {
	fraction tmp(*this);
	if(tmp.fract.first.num_of_terms == 1 && tmp.fract.second.num_of_terms == 1) {
		term term_co1(tmp.fract.first.arr[0].coefficient, 1, 1);
		term term_co2(tmp.fract.second.arr[0].coefficient, 1, 1);
		term term_ro1(1, tmp.fract.first.arr[0].root, tmp.fract.first.arr[0].base);
		term term_ro2(1, tmp.fract.second.arr[0].root, tmp.fract.second.arr[0].base);

		fraction tmp_co(term_co1, term_co2);
		fraction tmp_ro(term_ro1, term_ro2);

		tmp_co.fract.first.arr[0].root = exponent;
		tmp_co.fract.second.arr[0].root = exponent;
		tmp_co.fract.first.arr[0].base = tmp_co.fract.first.arr[0].coefficient;
		tmp_co.fract.second.arr[0].base = tmp_co.fract.second.arr[0].coefficient;
		tmp_co.fract.first.arr[0].coefficient = 1;
		tmp_co.fract.first.arr[0].coefficient = 1;

		tmp_ro.fract.first.arr[0].root *= exponent;
		tmp_ro.fract.second.arr[0].root *= exponent;

		tmp = tmp_co * tmp_ro;

	}
	else {
		tmp.fract.second = 0;
	}
	tmp.value = pow(tmp.value, 1.0/double(exponent));
	return tmp;
}

fraction& fraction::
operator=(const fraction& r) {
	fract.first = r.fract.first;
	fract.second = r.fract.second;
	value = r.value;
	return *(this);
}

fraction& fraction::
operator=(const pair<terms, terms>& r) {
	fraction tmp(r);
	fract.first = tmp.fract.first;
	fract.second = tmp.fract.second;
	value = tmp.value;
	return *(this);
}

fraction& fraction::
operator=(const terms& r) {
	fraction tmp(r);
	fract.first = tmp.fract.first;
	fract.second = tmp.fract.second;
	value = tmp.value;
	return *(this);
}

fraction& fraction::
operator=(const term& r) {
	fraction tmp(r);
	fract.first = tmp.fract.first;
	fract.second = tmp.fract.second;
	value = tmp.value;
	return *(this);
}

fraction& fraction::
operator=(const int& r) {
	fraction tmp(r);
	fract.first = tmp.fract.first;
	fract.second = tmp.fract.second;
	value = tmp.value;
	return *(this);
}

fraction& fraction::
operator=(const double& r) {
	double denominator = 1.0;
	while(double(int(r * denominator)) != r * denominator)
		denominator *= 10.0;
	fract.first = int(r * denominator);
	fract.second = int(denominator);
	value = r;
	return *(this);//check this!
}

fraction& fraction::
operator=(const float& r) {
	float denominator = 1.0;
	while(float(int(r * denominator)) != r * denominator)
		denominator *= 10.0;
	fract.first = int(r * denominator);
	fract.second = int(denominator);
	value = double(r);
	return *(this);//check this!
}

/*
bool fraction::
operator>(const fraction& r) {
	double L = 0, R = 0;
	double denominator = 0;
	int i,j;
	term temp;

	for(i = 0 ; i < this -> fract.first.num_of_terms ; ++i){
		temp = this -> fract.first.arr[i];
		L += temp.coefficient * pow(temp.base, 1 / temp.root);
	}
	for(i = 0 ; i < this -> fract.second.num_of_terms ; ++i){
		temp = this -> fract.second.arr[i];
		denominator += temp.coefficient * pow(temp.base, 1 / temp.root);
	}

	L /= denominator;
	denominator = 0;

	for(i = 0 ; i < r.fract.first.num_of_terms ; ++i){
        temp = r.fract.first.arr[i];
        R += temp.coefficient * pow(temp.base, 1 / temp.root);
    }

	for(i = 0 ; i < r.fract.first.num_of_terms ; ++i){
        temp = r.fract.second.arr[i];
        denominator += temp.coefficient * pow(temp.base, 1 / temp.root);
	}

	return L > R/denominator;
}

bool fraction::
operator<(const fraction& r) {
		return !(*(this)>r && *(this) == r);
}
*/

bool operator==(const int& l, const fraction& r) {
	fraction tmp(l);
	return (tmp == r);
}

bool operator!=(const int& l, const fraction& r) {
	return !(l == r);
}

bool operator==(const fraction& l, const int& r) {
	return (r == l);
}

bool operator!=(const fraction& l, const int& r) {
	return !(r == l);
}


bool operator==(const double& l, const fraction& r) {
	fraction tmp(l);
	return (tmp == r);
}

bool operator!=(const double& l, const fraction& r) {
	return !(l == r);
}

bool operator==(const fraction& l, const double& r) {
	return (r == l);
}

bool operator!=(const fraction& l, const double& r) {
	return !(r == l);
}

bool operator==(const float& l, const fraction& r) {
	fraction tmp(l);
	return (tmp == r);
}

bool operator!=(const float& l, const fraction& r) {
	return !(l == r);
}

bool operator==(const fraction& l, const float& r) {
	return (r == l);
}

bool operator!=(const fraction& l, const float& r) {
	return !(r == l);
}

bool operator==(const pair<int, int>& l, const fraction& r) {
	fraction tmp(l);
	return (tmp == r);
}

bool operator!=(const pair<int, int>& l, const fraction& r) {
	return !(l == r);
}

bool operator==(const fraction& l, const pair<int, int>& r) {
	return (r == l);
}

bool operator!=(const fraction& l, const pair<int, int>& r) {
	return !(r == l);
}
  
bool operator==(const fraction& l, const fraction& r) {
	fraction tmpl(l);
	fraction tmpr(r);

	tmpl.simplify();
	tmpr.simplify();

	if(tmpl.fract.second == 0 && tmpr.fract.second == 0)
		if(tmpl.value == tmpr.value)
			return true;
	if(tmpl.fract.first == tmpr.fract.first && tmpl.fract.second == tmpr.fract.second)
		return true;
	return false;
}

bool operator!=(const fraction& l, const fraction& r) {
	return !(l == r);
}

fraction operator+(const fraction& l, const fraction& r){
	if(l.is_denominator_zero() || r.is_denominator_zero()){
		fraction temp(1,0);
		temp.value = l.value + r.value;
		return temp;
	}
	else{
		terms t1 = l.fract.first * r.fract.second + l.fract.second*r.fract.first,
			t2 = l.fract.second*r.fract.second;
		fraction p(make_pair(t1, t2));
		p.simplify();
		return p;
	}
}

fraction operator-(const fraction& l, const fraction& r){
	if(l.is_denominator_zero() || r.is_denominator_zero()){
		fraction temp(1,0);
		temp.value = l.value - r.value;
		return temp;
	}
	else{
		terms t1 = l.fract.first * r.fract.second - l.fract.second*r.fract.first,
			t2 = l.fract.second*r.fract.second;
		fraction p( make_pair(t1, t2) );
		p.simplify();
		return p;
	}
}

fraction operator*(const fraction& l, const fraction& r){
	if(l.is_denominator_zero() || r.is_denominator_zero()){
		fraction temp(1,0);
		temp.value = l.value * r.value;
		return temp;
	}
	else{
		terms t1 = l.fract.first * r.fract.first,
			t2 = l.fract.second * r.fract.second;
		fraction p(make_pair(t1, t2));
		p.simplify();
		return p;
	}
}

fraction operator/(const fraction& l, const fraction& r){
	if(l.is_denominator_zero() || r.is_denominator_zero()){
		fraction temp(1,0);
		temp.value = l.value / r.value;
		return temp;
	}
	else{
		fraction reverse_r( make_pair(r.fract.second , r.fract.first));
		fraction result = l * reverse_r;
		return result;
	}
}

fraction operator-(const fraction& rhs){
	if(rhs.is_denominator_zero()) {
		fraction result(1,0);
		result.value = -rhs.value;
		return result;
	}
	fraction result(-rhs.fract.first, rhs.fract.second);
	return result;
}

ostream& operator<<(ostream& out, const fraction& rhs){
	string str = rhs.fts().second;
	return out << str;
}

istream& operator>>(istream& in, fraction& rhs){
	string str;
	vector<bool> sign;
	vector<int> index;
	int term_num = 0;
	bool isFirstTermNeg, isInteger;
	size_t idx;
	cin >> str;
	idx = str.find("/");
	isInteger = (idx == -1);
	terms result[2];

	if(!isInteger)
		str[idx] = ' ';
	else
		str = str + " 1";

	string temp;
	istringstream iss(str);
	for(int i = 0 ; i < 2 ; ++i){
		iss >> temp;
		isFirstTermNeg = (temp[0] == '-');
		if(!isFirstTermNeg)
			sign.push_back(true);
		for(int k = 0 ; k < temp.size() ; ++k)
			if( temp[k] == '-' || temp[k] == '+'){
				sign.push_back(temp[k]=='+');
				index.push_back(k);
			}
		term_num = sign.size();
		for(int k = 0 ; k < index.size() ; ++k){
			temp[index[k]] = ' ';
		}

		istringstream iss2(temp);
		for(int k = 0 ; k < term_num ; ++k){
			string temp_string;
			iss2 >> temp_string;
			int idxR = temp_string.find('r'), idxV = temp_string.find('v');
			int base, root, coef;
			bool isR = (idxR != -1);
			bool isV = (idxV != -1);
			if(!isR && !isV){
				istringstream iss3(temp_string);
				iss3 >> coef;
				base = 1;
				root = 1;
				if(!sign[k]) coef = -coef;
				result[i].push_back(term(coef,root,base));
			}
			else if(!isR && isV){
				temp_string[idxV] = ' ';
				istringstream iss3(temp_string);
				if(idxV==0){
					iss3 >> base;
					coef = 1;
				}
				else
					iss3 >> coef >> base;
				root = 2;
				if(!sign[k]) coef = -coef;
				result[i].push_back(term(coef,root,base));
			}
			else if(isR && isV){
				temp_string[idxV] = ' ';
				temp_string[idxR] = ' ';
				istringstream iss3(temp_string);
				if(idxR==0){
					iss3 >> root >> base;
					coef = 1;
				}
				else
					iss3 >> coef >> root >> base;
				if(!sign[k]) coef = -coef;
				result[i].push_back(term(coef,root,base));
			}
		}
		sign.clear();
		index.clear();
	}
	rhs = make_pair(result[0], result[1]);
	return in;
}

matrix operator+ (const matrix& l, const matrix& r){
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

matrix operator- (const matrix& l, const matrix& r){
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

matrix operator* (const matrix& l, const matrix& r){
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
	if(matL.row != matR.row || matL.col != 1 || matR.col != 1)
		throw "error occurs in 'dotproduct(const martix& matL, const matrix& matR)'.\nyou can dotproduct between two vectors whose row is equal to each row.";
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
	fraction f(0);
	vector<fraction> temp;
	for(int i = 0 ; i < col ; ++i) temp.push_back(f);
	for(int i = 0 ; i < row ; ++i) arr.push_back(temp);
}

//square matrix일 때만 identity_matrix가 나오게 할까?
void matrix::
make_identity_matrix() {
	initialize();
	fraction f(1);
	for(int i = 0; i < min(row,col); i++)
		arr[i][i] = f;
}

void matrix::
make_all_entry_zero() {
	fraction zero_entry(0);
	for(int i = 0; i < row; i++)
		for(int j = 0; j < col; j++)
			arr[i][j] = zero_entry;
}

/*
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
*/
void matrix::
show(bool no_paranthesis){
	bool zero_test = false;
	matrix_simplification();
	for(int i = 0 ; i < row ; ++i)
		for(int j = 0 ; j < col ; ++j)
			zero_test = zero_test || get_arr()[i][j].is_denominator_zero();
	if(zero_test)
		show_double(no_paranthesis);

	else{
		if(row*col == 0) cout << "[]" << endl;
		else{
			int length[row][col] = {0,};
			int i = 0, j = 0, num = 0;
			vector<int> colMax, numv;
			string str[row][col];
			pair<int,string> ptemp;

			for(i = 0 ; i < row ; ++i)
				for(j = 0 ; j < col ; ++j){
					ptemp = arr[i][j].fts();
					length[i][j] = ptemp.first;
					str[i][j] = ptemp.second;
				}
	
			for(i = 0 ; i < col ; ++i){
				for(j = 0 ; j < row ; ++j)
					numv.push_back( length[j][i] );
				colMax.push_back(*max_element(numv.begin(), numv.end()));
				numv.clear();
			}
	
			for(i = 0 ; i < row ; ++i){
				if(!no_paranthesis) cout << '[' << ' ';
				else cout << ' ';
				for(int j = 0 ; j < col ; ++j){
					blank(colMax[j] - length[i][j]);
					cout << str[i][j] << ' ';
				}
				if(!no_paranthesis) cout << ']' << endl;
				else cout << endl;
			}
		}
	}
}
void matrix::
show_double(bool no_paranthesis) {
	if(row*col == 0) cout << "[]" << endl;
	else{
		int i, j;
		bool neg[col];
		for(i = 0 ; i < col ; ++i)
			neg[i] = false;

		for(i = 0 ; i < col ; ++i)
			for(j = 0 ; j < row ; ++j)
				if( get_arr()[j][i].value < 0)
					neg[i] = true;

		cout << setprecision(5) << fixed;
		for(i = 0 ; i <row ; ++i){
			if(!no_paranthesis) cout << '[' << ' ';
			else cout << ' ';
			for(j = 0 ; j < col ; ++j){
				if(get_arr()[i][j].value > 0 && neg[j])
					blank(1);
				cout << get_arr()[i][j].value << ' ';
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
normalize() {
	if(col != 1)
		throw  "error occurs in 'matrix::normalize()'.\nyou can nomarlize when 'matrix::col' is 1.";
	fraction length(0);

	for(int i = 0; i < row; i++) {
		length = length + arr[i][0].power(2);
	}
	length = length.root(2);
	matrix result = *this;
	for(int i = 0; i < row; i++)
		result.arr[i][0] = result.arr[i][0] / length;
	return result;
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

	result.set_arr(this -> get_row() - 1, this -> get_row() - 1, make_entry(0,1));
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
				//	temp.show();
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
		throw "error occurs in 'matrix::project(const matrix& mat)'.\nyou can project correct vector.";
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

matrix matrix::
gram_schmidt() {
	if(row < col) 
		throw "error occurs in matrix::gram_schmidt(). You can use gram-schmidt process when row >= col.";
	matrix* col_arr = new matrix[col];
	for(int i = 0; i < col; i++) {
		col_arr[i] = matrix(row, 1);
		for(int j = 0; j < row; j++) {
			col_arr[i].arr[j][0] = arr[j][i];
		}
	}
	matrix* result_col_arr = new matrix[col];
	for(int i = 0; i < col; i++) {
		result_col_arr[i] = matrix(row, 1);
		for(int j = 0; j < row; j++) {
			result_col_arr[i].arr[j][0] = arr[j][i];
		}
	}

	for(int i = 0; i < col - 1; i++) {
		for(int j = 0; j < i + 1; j++) {
			result_col_arr[i+1] = result_col_arr[i+1] - (dotproduct(result_col_arr[j], col_arr[i+1])*(fraction(1)/dotproduct(result_col_arr[j], result_col_arr[j])))*result_col_arr[j];
		}
	}
	for(int i = 0; i < col; i++) { 
		result_col_arr[i] = result_col_arr[i].normalize();
	}
	matrix result(row, col);
	for(int i = 0; i < row; i++)
		for(int j = 0; j < col; j++)
			result.arr[i][j] = result_col_arr[j].arr[i][0];
	delete[] col_arr;
	delete[] result_col_arr;
	return result;
}

matrix matrix::
Rfactor() {
	if(row < col)
		throw "error occurs in matrix::Rfactor(). You can QRfactorize when row >= col.";
	matrix* A = new matrix[col];
	for(int i = 0; i < col; i++) {
		A[i] = matrix(row, 1);
		for(int j = 0; j < row; j++) {
			A[i].arr[j][0] = arr[j][i];
		}
	}

	matrix gram_sh = gram_schmidt();
	matrix* Q = new matrix[col];
	for(int i = 0; i < col; i++) {
		Q[i] = matrix(row, 1);
		for(int j = 0; j < row; j++) {
			Q[i].arr[j][0] = gram_sh.arr[j][i];
		}
	}
	matrix R(col, col);
	for(int i = 0; i < col; i++) {
		for(int j = 0; j < i+1; j++) {
			R.arr[j][i] = dotproduct(Q[j], A[i]);
		}
	}
	delete[] A;
	delete[] Q;

	return R;
}






bool compare_value(fraction f1, fraction f2){
	return f1.getValue() < f2.getValue();
}

vector<fraction> matrix::
eigenvalue() {
	matrix temp = *this;
	vector<fraction> v;
	int i, j;
	fraction tempf;
	if(row!=col){
		cout << "not square matrix" << endl;
		return v;
	}
	else{
		temp = temp.eliminate();
		for(i = 0 ; i < row ; ++i)
			v.push_back(temp.get_arr()[i][i]);
		sort(v.begin(), v.end(), compare_value);

		for(i = 0 ; i < v.size() ; ++i){
			tempf = v[i];
			for(j = i + 1 ; j < v.size() ; ++j)
				if(tempf == v[j]){
					v.erase( v.begin() + j);
					j--;
				}
		}
	}
	sort(v.begin(), v.end(), compare_value);

	return v;
}

