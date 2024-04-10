#include "fraction.h"
#include <iostream>
#include <cassert>

namespace cs_fraction {
	//ASK ABOUT THE VALUE OF "-x+y/z" ON WED. DOES IT EQUAL -x + y/z, OR IS IT -(x + y/z)? FIND OUT.
	Fraction::Fraction(int numer, int denom) {
		assert(denom != 0);
		this->numer = numer;
		this->denom = denom;
		(*this).simplify();
	}






	void Fraction::simplify() {
		// handle 0/x
		if (numer == 0) {
			denom = 1;
			return;
		}

		// handle signs of numerator & denominator
		if (denom < 0) {
			numer *= -1;
			denom *= -1;
		}

		// find gcf
		int gcf = 1;
		int greatest = denom;
		if (numer > denom) {
			greatest = numer;
		}
		if (numer % denom == 0) {
			gcf = denom;
		}
		for (int i = gcf; i <= denom / 2 + 1; i++) {
			if (denom % i == 0 && numer % i == 0) {
				gcf = i;
			}
		}

		// modify numerator & denominator
		numer /= gcf;
		denom /= gcf;
	}






	std::ostream& operator<< (std::ostream& out, const Fraction& frac) {
		if (frac.denom == 1) {
			std::cout << frac.numer;
		}
		else if (fabs(frac.numer) < frac.denom) {
			std::cout << frac.numer << '/' << frac.denom;
			}
		else {
			std::cout << frac.numer / frac.denom << '+' << fabs(frac.numer % frac.denom) << '/' << frac.denom;
		}
		return out;
	}






	std::istream& operator>> (std::istream& in, Fraction& f) {
		int inData[3] = { 1, 1, 1 };
		int i = 0;
		while (isspace(in.peek())) {
			in.ignore();
		}
		while (!isspace(in.peek()) && in.peek() != -1) {
			in >> inData[i];
			i++;
			if (!isspace(in.peek())) {
				in.ignore();
			}
		}
		switch (i) {
		case 1:
		case 2:
			f.numer = inData[0];
			f.denom = inData[1];
			break;
		case 3:
			f.numer = (inData[0] / fabs(inData[0])) * inData[1] + (inData[0] * inData[2]);
			f.denom = inData[2];
		default:
			break;
		}
		f.simplify();
		return in;
	}






	Fraction operator+(const Fraction& left, const Fraction& right) {
		int sumNumer = (left.numer * right.denom) + (right.numer * left.denom);
		int sumDenom = left.denom * right.denom;
		Fraction sum(sumNumer, sumDenom);
		return sum;
	}






	Fraction Fraction::operator+=(const Fraction& right) {
		*this = *this + right;
		return *this;
	}






	Fraction Fraction::operator++() {
		this->numer += this->denom;
		return *this;
	}






	Fraction Fraction::operator++(int) {
		Fraction temp = *this;
		this->numer += this->denom;
		return temp;
	}






	Fraction operator-(const Fraction& left, const Fraction& right) {
		int diffNumer = (left.numer * right.denom) - (right.numer * left.denom);
		int diffDenom = left.denom * right.denom;
		Fraction difference(diffNumer, diffDenom);
		return difference;
	}






	Fraction Fraction::operator-=(const Fraction& right) {
		*this = *this - right;
		return *this;
	}






	Fraction Fraction::operator--() {
		this->numer -= this->denom;
		return *this;
	}






	Fraction Fraction::operator--(int) {
		Fraction temp = *this;
		this->numer -= this->denom;
		return temp;
	}






	Fraction operator*(const Fraction& left, const Fraction& right) {
		int prodNumer = left.numer * right.numer;
		int prodDenom = left.denom * right.denom;
		Fraction product(prodNumer, prodDenom);
		return product;
	}






	Fraction Fraction::operator*=(const Fraction& right) {
		*this = *this * right;
		return *this;
	}






	Fraction operator/(const Fraction& left, const Fraction& right) {
		int quotNumer = left.numer * right.denom;
		int quotDenom = left.denom * right.numer;
		Fraction quotient(quotNumer, quotDenom);
		return quotient;
	}






	Fraction Fraction::operator/=(const Fraction& right) {
		*this = *this / right;
		return *this;
	}






	bool operator==(const Fraction& left, const Fraction& right) {
		return(left.numer * right.denom == right.numer * left.denom);
	}






	bool operator!=(const Fraction& left, const Fraction& right) {
		return !(left == right);
	}






	bool operator>(const Fraction& left, const Fraction& right) {
		return(left.numer * right.denom > right.numer * left.denom);
	}






	bool operator<(const Fraction& left, const Fraction& right) {
		return(left.numer * right.denom < right.numer * left.denom);
	}






	bool operator<=(const Fraction& left, const Fraction& right) {
		return !(left > right);
	}






	bool operator>=(const Fraction& left, const Fraction& right) {
		return !(left < right);
	}
}