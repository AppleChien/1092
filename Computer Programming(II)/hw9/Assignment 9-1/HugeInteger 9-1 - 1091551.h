// HugeInteger class template definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

#include "deque - 1091551 - hw9.h"

//#include <deque>
//using std::deque;

template< typename T >
class HugeInteger : public deque< T >
{
public:
	HugeInteger(size_t n = 0); // constructor; construct a zero HugeInteger with mySize n

	// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
	HugeInteger(const HugeInteger& integerToCopy);

	~HugeInteger(); // destructor; destroys the HugeInteger

	const HugeInteger& operator=(const HugeInteger& right); // assignment operator

	void operator=(const deque< T >& right); // assignment operator

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
	void divideByTen();   // divides a HugeInteger by 10
	void helpIncrement(); // increments a HugeInteger by 1
	void helpDecrement(); // decrements a HugeInteger by 1
}; // end class template HugeInteger

#endif


// constructor; construct a zero HugeInteger with mySize n
template< typename T >
HugeInteger< T >::HugeInteger(size_t n)
	: deque< T >((n == 0) ? 1 : n)
{
}

// copy constructor; constructs a HugeInteger with a copy of each of the elements in integerToCopy
template< typename T >
HugeInteger< T >::HugeInteger(const HugeInteger< T >& integerToCopy)
	: deque< T >(integerToCopy)
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
const HugeInteger< T >& HugeInteger< T >::operator=(const HugeInteger< T >& right)
{
	if (&right != this) // avoid self-assignment
		typename deque< T >::operator=(right);

	return *this; // enables x = y = z, for example
} // end function operator=

template< typename T >
void HugeInteger< T >::operator=(const deque< T >& right)
{
	typename deque< T >::operator=(right);
}

// function that tests if one HugeInteger< T > is less than another
//作業
template< typename T >
bool HugeInteger< T >::operator<(HugeInteger< T >& right)
{
	unsigned int Size = this->size();
	unsigned int rightSize = right.size();
	if (Size < rightSize) {
		return true;
	}
	else if (Size > rightSize) {
		return false;
	}
	else { // Size == rightSize
		typename deque< T >::iterator it1 = --(this->end());
		typename deque< T >::iterator it2 = --(right.end());

		for (int a = right.size() - 1; a >= 0; a--, it1--, it2--) {
			if (*it1 > * it2)
				return false;
			else if (*it1 < *it2)
				return true;
		}
		return false;
	}

} // end function operator<

// function that tests if one HugeInteger< T > is less than or equal to another
template< typename T >
bool HugeInteger< T >::operator<=(HugeInteger< T >& right)
{
	return (*this == right || *this < right);
}

// addition operator; HugeInteger< T > + HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator+(HugeInteger< T >& op2)
{
	size_t op1Size = this->size();
	size_t op2Size = op2.size();
	size_t sumSize = (op1Size >= op2Size) ? op1Size + 1 : op2Size + 1;

	HugeInteger sum(sumSize);
	typename deque< T >::iterator it1 = this->begin();
	typename deque< T >::iterator it3 = sum.begin();
	for (; it1 != this->end(); ++it1, ++it3)
		*it3 = *it1;

	typename deque< T >::iterator it2 = op2.begin();
	it3 = sum.begin();
	for (; it2 != op2.end(); ++it2, ++it3)
		*it3 += *it2;

	it3 = sum.begin();
	typename deque< T >::iterator it4 = it3;
	for (++it4; it4 != sum.end(); ++it3, ++it4)
		if (*it3 > 9)
		{
			(*it3) -= 10;
			(*it4)++;
		}

	if (*it3 == 0)
		sum.erase(--(sum.end()));

	return sum;
} // end function operator+

// subtraction operator; HugeInteger< T > - HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator-(HugeInteger< T >& op2)
{
	HugeInteger zero;
	if (*this == op2)
		return zero;

	HugeInteger difference(*this);
	unsigned int op1Size = this->size();
	unsigned int op2Size = op2.size();
	unsigned int differenceSize = (op1Size >= op2Size) ? op1Size : op2Size;

	typename deque< T >::iterator it1 = this->begin();
	typename deque< T >::iterator it3 = difference.begin();
	for (; it1 != this->end(); ++it1, ++it3)
		*it3 = *it1;

	typename deque< T >::iterator it2 = op2.begin();
	it3 = difference.begin();
	typename deque< T >::iterator it4 = it3; //it4=it3的前一項
	typename deque< T >::iterator it5;
	for (it3; it2 != op2.end(); ++it2, ++it3) {
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
				it5 = it4;//it5=it4的前一項
				for (it5++; it4 != difference.end(); i++, it4++, it5++) {
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

	typename deque< T >::const_iterator it6 = --(difference.cend());
	for (int i = difference.size() - 1; i > 0 && *it6 == 0; i--) {
		difference.erase(--(difference.cend()));
		it6 = --(difference.cend());
	}

	return difference;
} // end function operator-

// multiplication operator; HugeInteger< T > * HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator*(HugeInteger< T >& op2)
{
	HugeInteger zero;
	if (isZero() || op2.isZero())
		return zero;

	HugeInteger product(this->size() + op2.size());
	for (typename deque< T >::iterator it1 = op2.begin(), it2 = product.begin(); it1 != op2.end(); ++it1, ++it2) {
		for (typename deque< T >::iterator it3 = this->begin(), it4 = it2; it3 != this->end(); ++it3, ++it4) {
			*it4 += *it1 * *it3;
		}
	}

	typename deque< T >::iterator it6 = product.begin();
	typename deque< T >::iterator it5 = it6; //it5=it6的後一項
	for (it6, ++it5; it6 != product.end(); ++it6, ++it5) {
		if (*it6 >= 10) {
			*it5 += *it6 / 10;
			*it6 %= 10;
		}
	}


	typename deque< T >::const_iterator it7 = --(product.cend());
	for (int i = product.size() - 1; i > 0 && *it7 == 0; i--) {
		product.erase(--(product.cend()));
		it7 = --(product.cend());
	}

	return product;
} // end function operator*

// division operator; HugeInteger< T > / HugeInteger< T > provided that the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator/(HugeInteger< T >& op2)
{
	HugeInteger zero;
	if (*this < op2)
		return zero;

	HugeInteger remainder(*this);
	HugeInteger buffer(this->size());

	int n = this->size() - op2.size();
	typename deque< T >::iterator it1 = op2.begin();
	typename deque< T >::iterator it2 = buffer.begin();

	for (int i = 0; i < n; ++i, ++it2); //buffer移位
	for (; it1 != op2.end(); it1++, it2++)
		*it2 = *it1;

	if (remainder < buffer)
		buffer.divideByTen();
	else
		n++;

	HugeInteger quotient(n);
	typename deque< T >::iterator it4 = quotient.end();
	--it4;
	for (int a = quotient.size() - 1; a >= 0; a--, --it4) {
		while (buffer <= remainder) {
			remainder = remainder - buffer;
			(*it4)++;
			if (remainder.isZero())
				return quotient;
		}
		buffer.divideByTen();
	}
	return quotient;
} // end function operator/

// modulus operator; HugeInteger< T > % HugeInteger< T > provided that the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator%(HugeInteger< T >& op2)
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
	typename deque< T >::iterator it = this->begin();
	for (; it != this->end(); ++it)
		if (*it != 0)
			return false;

	return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
template< typename T >
void HugeInteger< T >::divideByTen()
{
	typename deque< T >::iterator it1 = this->begin();
	typename deque< T >::iterator it2 = it1;
	for (++it2; it2 != this->end(); ++it1, ++it2)
		*it1 = *it2;

	this->erase(--this->end());
}

// function to help increment the integer
template< typename T >
void HugeInteger< T >::helpIncrement()
{
	typename deque< T >::iterator it = this->begin();
	if (isZero())
		(*it)++;
	else
	{
		(*it)++;
		typename deque< T >::iterator it2 = it;
		for (++it2; it2 != this->end(); ++it, ++it2)
			if (*it == 10)
			{
				*it = 0;
				(*it2)++;
			}

		if ((*it) == 10)
		{
			*it = 0;
			this->insert(this->end(), 1);
		}
	}
}

// function to help decrement the integer
template< typename T >
void HugeInteger< T >::helpDecrement()
{
	typename deque< T >::iterator it = this->begin();
	for (; *it == 0; ++it)
		*it = 9;

	(*it)--;

	if (!this->isZero() && this->back() == 0)
		this->erase(--(this->end()));
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream& operator<<(ostream& output, HugeInteger< T > hugeInteger)
{
	if (hugeInteger.isZero())
		output << 0;
	else
	{
		typename deque< T >::reverse_iterator it = hugeInteger.rbegin();
		for (; it != hugeInteger.rend(); ++it)
			if (*it < 10)
				output << *it;
	}

	return output; // enables cout << x << y;
}