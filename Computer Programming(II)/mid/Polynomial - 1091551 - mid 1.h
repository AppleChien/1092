#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <cmath>
using std::sqrt;

// Represents a term of a polynomial
struct Term
{
	bool operator!=(const Term& right) const
	{
		return coef != right.coef || expon != right.expon;
	}

	int coef;
	int expon;
};

// Polynomial class template definition
template< typename T >
class Polynomial
{
	// Overloaded stream insertion operator
	template< typename T >
	friend ostream& operator<<(ostream& output, Polynomial< T > a);
public:

	// Constructs an empty polynomial, with no terms.
	Polynomial(size_t n = 0)
		: polynomial(n)
	{
	}

	// Constructs a polynomial with a copy of each of the terms in polynomialToCopy.
	Polynomial(const Polynomial& right)
		: polynomial(right.polynomial)
	{
	}

	// Destructor with empty body
	~Polynomial()
	{
	}

	// Copies all the terms from "right" into the polynomial
	const Polynomial< T > operator=(const Polynomial& right)
	{
		if (&right != this) // avoid self-assignment
			polynomial = right.polynomial;

		return *this; // enables x = y = z, for example
	}

	bool operator==(const Polynomial& right)
	{
		return polynomial == right.polynomial;
	}

	void setPolynomial(int coefficient[], int exponent[], int numTerms)
	{
		for (int i = 0; i < numTerms; i++)
		{
			polynomial[i].coef = coefficient[i];
			polynomial[i].expon = exponent[i];
		}
	}

	// addition assignment operator; Polynomial< T > += Polynomial< T >
	void operator+=(Polynomial& op2)
	{
		Polynomial< T > sum;
		typename T::iterator it1 = polynomial.begin();
		typename T::iterator it2 = op2.polynomial.begin();
		while (it1 != polynomial.end() && it2 != op2.polynomial.end()) {
			if (it1->expon > it2->expon) {
				sum.attach(it1->coef, it1->expon);
				++it1;
			}
			else if (it1->expon < it2->expon) {
				sum.attach(it2->coef, it2->expon);
				++it2;
			}
			else {//it1->expon == it2->expon
				if (it1->coef + it2->coef != 0)
					sum.attach(it1->coef + it2->coef, it1->expon);
				++it1;
				++it2;
			}
		}
		for (; it1 != polynomial.end(); ++it1) {
			sum.attach(it1->coef, it1->expon);
		}
		for (; it2 != op2.polynomial.end(); ++it2) {
			sum.attach(it2->coef, it2->expon);
		}
		//return sum;
		*this = sum;
	}

	// subtraction assignment operator; Polynomial< T > -= Polynomial< T >
	void operator-=(Polynomial& op2)
	{
		Polynomial< T > minus = -op2;
		*this += minus;
	}

	// multiplication operator; Polynomial< T > * Polynomial< T >
	Polynomial< T > operator*(Polynomial& op2)
	{
		Polynomial< T > product;

		if (zero() || op2.zero()) {
			return 0;
		}
		else {
			for (typename T::iterator it2 = op2.polynomial.begin(); it2 != op2.polynomial.end(); ++it2) {
				Polynomial< T > buffer;
				for (typename T::iterator it1 = polynomial.begin(); it1 != polynomial.end(); ++it1) {
					buffer.attach(it1->coef * it2->coef, it1->expon + it2->expon);
				}
				product += buffer;
			}
			return product;
		}
	}

	// computes the square root of the current polynomial
	Polynomial< T > compSquareRoot()
	{
		Polynomial< T > remainder(*this);
		Polynomial< T > divisor;
		Polynomial< T > monomial(1);
		Polynomial< T > squareRoot;
		Polynomial< T > buffer;

		if (remainder.zero()) {
			return 0;
		}

		monomial.polynomial[0].expon = (remainder.polynomial[0].expon) / 2;
		monomial.polynomial[0].coef = sqrt(remainder.polynomial[0].coef);
		squareRoot.attach(monomial.polynomial[0].coef, monomial.polynomial[0].expon);
		divisor.attach(monomial.polynomial[0].coef, monomial.polynomial[0].expon);

		typename T::iterator it2 = remainder.polynomial.begin();
		typename T::iterator it3 = divisor.polynomial.begin();

		buffer.attach(monomial.polynomial[0].coef * it3->coef, monomial.polynomial[0].expon + it3->expon);
		remainder -= buffer;
		divisor.polynomial[divisor.polynomial.size() - 1].coef *= 2;
		while (!remainder.zero() && remainder.degree() >= divisor.degree()) {
				monomial.polynomial.begin()->coef = remainder.polynomial.begin()->coef / divisor.polynomial.begin()->coef;//added
			    monomial.polynomial.begin()->expon = remainder.polynomial.begin()->expon - divisor.polynomial.begin()->expon;//added
				squareRoot.attach(monomial.polynomial[0].coef, monomial.polynomial[0].expon);
				divisor.attach(monomial.polynomial[0].coef, monomial.polynomial[0].expon);
				
				buffer = monomial * divisor;
				remainder -= buffer;
				divisor.polynomial[divisor.polynomial.size() - 1].coef *= 2;
		}
		return squareRoot;
	}

private:
	T polynomial; // a polynomial

	// Attaches a new term to the polynomial
	void attach(int coefficient, int exponent)
	{
		Term tempTerm;
		tempTerm.coef = coefficient;
		tempTerm.expon = exponent;
		polynomial.push_back(tempTerm);
	}

	// Returns the minus of the current polynomial
	Polynomial< T > operator-()
	{
		Polynomial< T > minus(polynomial.size());
		typename T::iterator it2 = minus.polynomial.begin();
		typename T::iterator it1 = polynomial.begin();
		for (; it1 != polynomial.end(); ++it1, ++it2)
		{
			it2->coef = -it1->coef;
			it2->expon = it1->expon;
		}

		return minus;
	}

	// Returns true if and only if polynomial is a zero polynomial
	bool zero() const
	{
		return polynomial.empty();
	}

	// Returns the highest of degrees of polynomial's terms
	int degree() const
	{
		if (polynomial.empty())
			return 0;
		else
			return polynomial.begin()->expon;
	}

}; // end class template Polynomial

// Overloaded stream insertion operator
template< typename T >
ostream& operator<<(ostream& output, Polynomial< T > a)
{
	if (a.zero())
	{
		output << 0 << endl;
		return output;
	}

	typename T::iterator it = a.polynomial.begin();

	if (it->coef < 0)
		cout << "-" << -it->coef;
	else if (it->coef > 0)
		cout << it->coef;

	if (it->expon > 0)
	{
		if (it->expon == 1)
			cout << "x";
		else
			cout << "x^" << it->expon;
	}

	for (++it; it != a.polynomial.end(); ++it)
	{
		if (it->coef < 0)
			cout << " - " << -it->coef;
		else if (it->coef > 0)
			cout << " + " << it->coef;

		if (it->expon > 0)
		{
			if (it->expon == 1)
				cout << "x";
			else
				cout << "x^" << it->expon;
		}
	}

	return output; // enables cout << x << y;
} // end function operator<<

#endif