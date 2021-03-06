// HugeInteger class template definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

#include "vector - 1091551 - hw7-3.h" // include definition of class template vector
#include "list - 1091551 - hw7-3.h"   // include definition of class template list

/*
#include <vector> // include definition of class template vector
#include <list>   // include definition of class template list
using std::vector;
using std::list;
*/

template< typename T >
class HugeInteger
{
	template< typename T >
	friend ostream& operator<<(ostream& output, HugeInteger< T > hugeInteger);
public:
	HugeInteger(size_t n = 0); // constructor; construct a zero HugeInteger with mySize n

	// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
	HugeInteger(const HugeInteger& integerToCopy);

	~HugeInteger(); // destructor; destroys the HugeInteger

	const HugeInteger& operator=(const HugeInteger& right); // assignment operator

	// assign right to integer, i.e., integer = right
	void operator=(T& right);

	bool operator==(HugeInteger& right); // less than or equal to
	bool operator<(HugeInteger& right);  // less than
	bool operator<=(HugeInteger& right); // less than or equal to

	// addition operator; HugeInteger + HugeInteger
	HugeInteger operator+(HugeInteger& op2);

	// subtraction operator; HugeInteger - HugeInteger provided that
	// the minuend is greater than or equal to the subtrahend
	HugeInteger operator-(HugeInteger& op2);

	// multiplication operator; HugeInteger * HugeInteger
	HugeInteger operator*(HugeInteger& op2);

	// division operator; HugeInteger / HugeInteger
	// provided that the divisor is not equal to 0
	HugeInteger operator/(HugeInteger& op2);

	// modulus operator; HugeInteger % HugeInteger
	// provided that the divisor is not equal to 0
	HugeInteger operator%(HugeInteger& op2);

	HugeInteger& operator++(); // prefix increment operator

	HugeInteger operator++(int); // postfix increment operator

	HugeInteger& operator--(); // prefix decrement operator

	HugeInteger operator--(int); // postfix decrement operator

	bool isZero(); // return true if and only if all digits are zero

private:
	T integer;

	void divideByTen();            // divides a HugeInteger by 10
	void helpIncrement();          // increments a HugeInteger by 1
	void helpDecrement();          // decrements a HugeInteger by 1
}; // end class template HugeInteger

#endif

// constructor; construct a zero HugeInteger with mySize n
template< typename T >
HugeInteger< T >::HugeInteger(size_t n)
	: integer((n > 0) ? n : 1)
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger(const HugeInteger& integerToCopy)
	: integer(integerToCopy.integer)
{
}

// destructor; destroys the HugeInteger
template< typename T >
HugeInteger< T >::~HugeInteger()
{
}

// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
template< typename T >
const HugeInteger< T >& HugeInteger< T >::operator=(const HugeInteger& right)
{
	if (&right != this) // avoid self-assignment
		integer = right.integer;

	return *this; // enables x = y = z, for example
}

template< typename T >
void HugeInteger< T >::operator=(T& right)
{
	integer = right;
}

// function that tests if two HugeIntegers are equal
template< typename T >
bool HugeInteger< T >::operator==(HugeInteger& right)
{
	return (integer == right.integer);
}

// function that tests if one HugeInteger< T > is less than another
template< typename T >
bool HugeInteger< T >::operator<(HugeInteger& right)
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
		typename T::iterator it1 = --(integer.end());
		typename T::iterator it2 = --(right.integer.end());

		for (int a = right.integer.size() - 1; a >= 0; a--, it1--, it2--) {
			if (*it1 > * it2)
				return false;
			else if (*it1 < *it2)
				return true;
		}
		return false;
	}

}

// function that tests if one HugeInteger< T > is less than or equal to another
template< typename T >
bool HugeInteger< T >::operator<=(HugeInteger& right)
{
	return (*this == right || *this < right);
}

// addition operator; HugeInteger< T > + HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator+(HugeInteger& op2)
{
	size_t op1Size = integer.size();
	size_t op2Size = op2.integer.size();
	size_t sumSize = (op1Size >= op2Size) ? op1Size + 1 : op2Size + 1;

	HugeInteger sum(sumSize);
	typename T::iterator it1 = integer.begin();
	typename T::iterator it3 = sum.integer.begin();
	for (; it1 != integer.end(); ++it1, ++it3)
		*it3 = *it1;

	typename T::iterator it2 = op2.integer.begin();
	it3 = sum.integer.begin();
	for (; it2 != op2.integer.end(); ++it2, ++it3)
		*it3 += *it2;

	it3 = sum.integer.begin();
	typename T::iterator it4 = it3;
	for (++it4; it4 != sum.integer.end(); ++it3, ++it4)
		if (*it3 > 9)
		{
			(*it3) -= 10;
			(*it4)++;
		}

	if (*it3 == 0)
		sum.integer.erase(--(sum.integer.cend()));

	return sum;
}

// subtraction operator; HugeInteger< T > - HugeInteger< T >
// provided that *this is greater than or equal to op2
template< typename T >
HugeInteger< T > HugeInteger< T >::operator-(HugeInteger& op2)
{
	HugeInteger zero;

	if (*this == op2)
		return zero;

	HugeInteger difference(*this);
	unsigned int op1Size = integer.size();
	unsigned int op2Size = op2.integer.size();
	unsigned int differenceSize = (op1Size >= op2Size) ? op1Size : op2Size;

	typename T::iterator it1 = integer.begin();
	typename T::iterator it3 = difference.integer.begin();
	for (; it1 != integer.end(); ++it1, ++it3)
		*it3 = *it1;

	typename T::iterator it2 = op2.integer.begin();
	it3 = difference.integer.begin();
	typename T::iterator it4 = it3; //it4=it3???e?@??
	typename T::iterator it5;
	for (it3; it2 != op2.integer.end(); ++it2, ++it3) {
		if (*it3 >= *it2)
			*it3 -= *it2;
		else { //*it3 < *it2
			(*it3) += 10;
			it4 = it3;
			it4++;
			if (*(it4) > 0)
				(*(it4))--;
			else {
				int i = 0;
				it5 = it4;//it5=it4???e?@??
				for (it5++; it4 != difference.integer.end(); i++, it4++, it5++) {
					*(it4) += 9;
					if (*(it5) > 0) {
						(*(it5))--;
						break;
					}
				}
			}
			*it3 -= *it2;
		}
	}
	
	typename T::const_iterator it6 = --(difference.integer.cend());
	for (int i = difference.integer.size() - 1; i > 0 && *it6 == 0; i--) {
		difference.integer.erase(--(difference.integer.cend()));
		it6 = --(difference.integer.cend());
	}

	return difference;
}

// multiplication operator; HugeInteger< T > * HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator*(HugeInteger& op2)
{
	HugeInteger zero;
	if (isZero() || op2.isZero())
		return zero;

	size_t op1Size = integer.size();
	size_t op2Size = op2.integer.size();
	size_t productSize = op1Size + op2Size;

	HugeInteger product(productSize);

	for (typename T::iterator it1 = op2.integer.begin(), it2 = product.integer.begin(); it1 != op2.integer.end(); ++it1, ++it2) {
		for (typename T::iterator it3 = integer.begin(), it4 = it2; it3 != integer.end(); ++it3, ++it4) {
			*it4 += *it1 * *it3;
		}
	}

	typename T::iterator it6 = product.integer.begin();
	typename T::iterator it5 = it6; //it5=it6?????@??
	for (it6, ++it5; it6 != product.integer.end(); ++it6, ++it5) {
		if (*it6 >= 10) {
			*it5 += *it6 / 10;
			*it6 %= 10;
		}
	}


	typename T::const_iterator it7 = --(product.integer.cend());
	for (int i = product.integer.size() - 1; i > 0 && *it7 == 0; i--) {
		product.integer.erase(--(product.integer.cend()));
		it7 = --(product.integer.cend());
	}
	return product;
}

// division operator; HugeInteger< T > / HugeInteger< T >
// provided that op2 is not zero
template< typename T >
HugeInteger< T > HugeInteger< T >::operator/(HugeInteger& op2)
{
	HugeInteger zero;
	if (*this < op2)
		return zero;

	HugeInteger remainder(*this);
	HugeInteger buffer(integer.size());

	int n = integer.size() - op2.integer.size();
	typename T::iterator it1 = op2.integer.begin();
	typename T::iterator it2 = buffer.integer.begin();

	for (int i = 0; i < n; ++i, ++it2); //buffer????
	for (; it1 != op2.integer.end(); it1++, it2++)
		*it2 = *it1;

	if (remainder < buffer)
		buffer.divideByTen();
	else
		n++;

	HugeInteger quotient(n);
	typename T::iterator it4 = quotient.integer.end();
	--it4;
	for (int a = quotient.integer.size()-1; a >= 0; a--, --it4) {
		while (buffer <= remainder) {
			remainder = remainder - buffer;
			(*it4)++;
			if (remainder.isZero())
				return quotient;
		}
		buffer.divideByTen();
	}
	return quotient;
}

// modulus operator; HugeInteger< T > % HugeInteger< T >
// provided that op2 is not zero
template< typename T >
HugeInteger< T > HugeInteger< T >::operator%(HugeInteger& op2)
{
	HugeInteger quotient = (*this) / op2;
	HugeInteger product = quotient * op2;
	HugeInteger remainder = (*this) - product;
	return remainder;
}

// overloaded prefix increment operator 
template< typename T >
HugeInteger< T >& HugeInteger< T >::operator++()
{
	helpIncrement(); // increment integer
	return *this; // reference return to create an lvalue
}

// overloaded postfix increment operator;
// note that the dummy integer parameter does not have a parameter name
template< typename T >
HugeInteger< T > HugeInteger< T >::operator++(int)
{
	HugeInteger temp = *this; // hold current state of object
	helpIncrement();

	// return unincremented, saved, temporary object
	return temp; // value return; not a reference return
}

// overloaded prefix decrement operator 
template< typename T >
HugeInteger< T >& HugeInteger< T >::operator--()
{
	helpDecrement(); // increment integer
	return *this; // reference return to create an lvalue
}

// overloaded postfix decrement operator;
// note that the dummy integer parameter does not have a parameter name
template< typename T >
HugeInteger< T > HugeInteger< T >::operator--(int)
{
	HugeInteger temp = *this; // hold current state of object
	helpDecrement();

	// return unincremented, saved, temporary object
	return temp; // value return; not a reference return
}

// function that tests if a HugeInteger is zero
template< typename T >
bool HugeInteger< T >::isZero()
{
	typename T::iterator it = integer.begin();
	for (; it != integer.end(); ++it)
		if (*it != 0)
			return false;

	return true;
}

// function that divides a HugeInteger by 10;
// shift a HugeInteger one position to the right
template< typename T >
void HugeInteger< T >::divideByTen()
{
	typename T::iterator it1 = integer.begin();
	typename T::iterator it2 = it1;
	for (++it2; it2 != integer.end(); ++it1, ++it2)
		*it1 = *it2;

	integer.erase(--integer.cend());
}

// function to help increment the integer
template< typename T >
void HugeInteger< T >::helpIncrement()
{
	typename T::iterator it = integer.begin();
	if (isZero())
		(*it)++;
	else
	{
		(*it)++;
		typename T::iterator it2 = it;
		for (++it2; it2 != integer.end(); ++it, ++it2)
			if (*it == 10)
			{
				*it = 0;
				(*it2)++;
			}

		if ((*it) == 10)
		{
			*it = 0;
			integer.insert(integer.cend(), 1);
		}
	}
}

// function to help decrement the integer
template< typename T >
void HugeInteger< T >::helpDecrement()
{
	typename T::iterator it = integer.begin();
	for (; *it == 0; ++it)
		*it = 9;

	(*it)--;

	if (!isZero() && integer.back() == 0)
		integer.erase(--(integer.cend()));
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream& operator<<(ostream& output, HugeInteger< T > hugeInteger)
{
	if (hugeInteger.isZero())
		output << 0;
	else
	{
		typename T::reverse_iterator it = hugeInteger.integer.rbegin();
		for (; it != hugeInteger.integer.rend(); ++it)
			if (*it < 10)
				output << *it;
	}

	return output; // enables cout << x << y;
}