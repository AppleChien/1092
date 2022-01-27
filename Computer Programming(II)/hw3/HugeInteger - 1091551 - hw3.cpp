// Member-function definitions for class HugeInteger
#include <iostream>
using namespace std;
#include "HugeInteger.h" // include definition of class HugeInteger

// default constructor; construct a zero HugeInteger with size 1
HugeInteger::HugeInteger()
	: integer(1)
{
}

// constructor; construct a zero HugeInteger with size n
HugeInteger::HugeInteger(unsigned int n)
	: integer((n > 0) ? n : 1)
{
} // end HugeInteger constructor

// copy constructor
// constructs a HugeInteger with a copy of each of the elements in integerToCopy
HugeInteger::HugeInteger(const HugeInteger& integerToCopy)
	: integer(integerToCopy.integer)
{
} // end HugeInteger copy constructor

// destructor; destroys the HugeInteger
HugeInteger::~HugeInteger()
{
} // end HugeInteger destructor

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
const HugeInteger& HugeInteger::assign(const HugeInteger& right)
{
	if (&right != this) // avoid self-assignment
		integer.assign(right.integer);

	return *this; // enables x = y = z, for example
}

// function that tests if two HugeIntegers are equal
bool HugeInteger::equal(const HugeInteger& right) const
{
	unsigned int Size = integer.size();
	unsigned int rightSize = right.integer.size();
	if (Size != rightSize) {
		return false;
	}
	else // Size == rightSize
	{
		vector::const_iterator it1 = integer.begin();
		vector::const_iterator it3 = right.integer.begin();
		for (;it1 != integer.end();++it1, ++it3) {
			if (*it1 != *it3)
				return false;
		}
		return true;
	}

} // end function equal

// function that tests if one HugeInteger is less than another
bool HugeInteger::less(const HugeInteger& right) const
{
	unsigned int Size = integer.size();
	unsigned int rightSize = right.integer.size();
	if (Size < rightSize) {
		return true;
	}
	else if (Size > rightSize) {
		return false;
	}
	else { // Size == rightSize
		vector::const_iterator it1 = integer.end() - 1;
		vector::const_iterator it3 = right.integer.end() - 1;
		for (it1;it1 >= integer.begin();it1--, it3--) {
			if (*it1 < *it3)
				return true;
			else if (*it1 > * it3)
				return false;
			else { //*it1 == *it3
				if (it1 == integer.begin())
					return false;
			}
		}
	}

} // end function less

// function that tests if one HugeInteger is less than or equal to another
bool HugeInteger::lessEqual(const HugeInteger& right) const
{
	return (less(right) || equal(right));
} // end function lessEqual

// addition operator; HugeInteger + HugeInteger
HugeInteger HugeInteger::add(HugeInteger& op2)
{
	unsigned int op1Size = integer.size();
	unsigned int op2Size = op2.integer.size();
	unsigned int sumSize = (op1Size >= op2Size) ? op1Size + 1 : op2Size + 1;

	HugeInteger sum(sumSize);

	vector::iterator it1 = integer.begin();
	vector::iterator it3 = sum.integer.begin();
	for (; it1 != integer.end(); ++it1, ++it3)
		*it3 = *it1;

	vector::iterator it2 = op2.integer.begin();
	for (it3 = sum.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3)
		*it3 += *it2;

	for (it3 = sum.integer.begin(); it3 != sum.integer.end() - 1; ++it3)
		if (*it3 > 9)
		{
			(*it3) -= 10;
			(*(it3 + 1))++;
		}

	if (*it3 == 0)
		sum.integer.erase(sum.integer.end() - 1);

	return sum;
} // end function add

// subtraction operator; HugeInteger - HugeInteger
HugeInteger HugeInteger::subtract(HugeInteger& op2)
{
	HugeInteger zero;

	if (equal(op2))
		return zero;

	HugeInteger difference(*this);
	unsigned int op1Size = integer.size();
	unsigned int op2Size = op2.integer.size();
	unsigned int differenceSize = (op1Size >= op2Size) ? op1Size : op2Size;

	//HugeInteger difference(differenceSize);

	vector::iterator it1 = integer.begin();
	vector::iterator it3 = difference.integer.begin();
	for (; it1 != integer.end(); ++it1, ++it3)
		*it3 = *it1;

	vector::iterator it2 = op2.integer.begin();
	for (it3 = difference.integer.begin(); it2 != op2.integer.end(); ++it2, ++it3)
		*it3 -= *it2;

	for (it3 = difference.integer.begin(); it3 != difference.integer.end() - 1; ++it3)
		if (*it3 < 0)
		{
			(*it3) += 10;
			(*(it3 + 1))--;
		}
	for (it3 = difference.integer.end() - 1;it3 >= difference.integer.begin();it3--) {
		if (*it3 == 0)
			difference.integer.erase(it3);
		else {
			break;
		}
	}

	return difference;
} // end function subtract

// multiplication operator; HugeInteger * HugeInteger
HugeInteger HugeInteger::multiply(HugeInteger& op2)
{
	HugeInteger zero;
	if (isZero() || op2.isZero())
		return zero;

	unsigned int productSize = integer.size() + op2.integer.size();
	HugeInteger product(productSize);

	for (size_t j = 0; j < op2.integer.size();j++) {
		for (size_t i = 0;i < integer.size();i++) {
			product.integer.begin()[i + j] += op2.integer.begin()[j] * integer.begin()[i];
		}
	}
	for (int i = 0; i < product.integer.size(); i++) {
		while (product.integer.begin()[i] > 9)
		{
			product.integer.begin()[i] -= 10;
			product.integer.begin()[i + 1]++;
		}
	}
	if (product.integer.begin()[product.integer.size() - 1] == 0)
		product.integer.erase(product.integer.end() - 1);

	return product;
} // end function multiply

// division operator; HugeInteger / HugeInteger provided that op2 is not zero
HugeInteger HugeInteger::divide(HugeInteger& op2)
{
	HugeInteger zero;
	if (less(op2) || isZero())
		return zero;
	HugeInteger remainder(*this);

	HugeInteger one(1);
	if (equal(op2)) {
		*one.integer.begin() = 1;
		return one;
	}

	//assign(remainder);
	HugeInteger buffer(integer.size());
	HugeInteger temp;

	int n = integer.size() - op2.integer.size();
	for (int i = op2.integer.size() - 1;i >= 0;i--) {
		buffer.integer.begin()[i + n] = op2.integer.begin()[i];
	}

	if (less(buffer))
		buffer.divideByTen();
	else
		n++;

	HugeInteger quotient(n);
	for (int k = quotient.integer.size() - 1;k >= 0;k--) {
		while (buffer.less(remainder) || buffer.equal(remainder)) {
			temp.assign(remainder.subtract(buffer));
			remainder.assign(temp.integer);
			quotient.integer.begin()[k]++;
			if (remainder.isZero())
				return quotient;
		}
		buffer.divideByTen();
	}
	return quotient;
}// end function divide

// modulus operator; HugeInteger % HugeInteger provided that op2 is not zero
HugeInteger HugeInteger::modulus(HugeInteger& op2)
{
	HugeInteger quotient = divide(op2);
	HugeInteger product = quotient.multiply(op2);
	HugeInteger remainder = subtract(product);
	return remainder;
}

// assign a vector of decimal digits into a HugeInteger
void HugeInteger::assign(const vector& v)
{
	integer.assign(v);
} // end function assign

// function that tests if a HugeInteger is zero
bool HugeInteger::isZero()
{
	for (vector::iterator it = integer.begin(); it != integer.end(); ++it)
		if (*it != 0)
			return false;

	return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
void HugeInteger::divideByTen()
{
	vector::iterator it = integer.begin();
	vector::iterator it2 = it;
	for (++it2; it2 != integer.end(); ++it, ++it2)
		*it = *it2;
	integer.erase(integer.end() - 1);
}

// overloaded output operator
void HugeInteger::output(ostream& outFile)
{
	vector::iterator it = integer.end() - 1;
	for (; it != integer.begin() - 1; --it)
		if (*it < 10)
			outFile << *it;
	outFile << endl;
} // end function output