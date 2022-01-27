// HugeInteger class definition.
#ifndef HUGEINTEGER_H
#define HUGEINTEGER_H

#include "list - 1091551 - hw7-2.h" // include definition of class vector 

template< typename T >
class HugeInteger
{
	template< typename T >
	friend ostream& operator<<(ostream& output, HugeInteger< T > hugeInteger);
public:
	HugeInteger(unsigned int n = 0); // constructor; construct a zero HugeInteger with size n

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

	bool isZero();           // return true if and only if all digits are zero
private:
	T integer;

	void divideByTen();            // divides a HugeInteger by 10
	void helpIncrement();          // increments a HugeInteger by 1
	void helpDecrement();          // decrements a HugeInteger by 1
}; // end class HugeInteger


// constructor; construct a zero HugeInteger with size n
template< typename T >
HugeInteger< T >::HugeInteger(unsigned int n)
	: integer((n == 0) ? 1 : n)
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
// return avoids: ( a1 = a2 ) = a3
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
} // end function operator==

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
		typename T::iterator it1 = integer.end()->prev;
		typename T::iterator it2 = right.integer.end()->prev;
		for (; it2 != right.integer.end(); it1 = it1->prev, it2 = it2->prev) {
			if (it1->myVal > it2->myVal)
				return false;
			else if (it1->myVal < it2->myVal)
				return true;
		}
		return false;
	}

} // end function operator<

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
	for (; it1 != integer.end(); it1 = it1->next, it3 = it3->next)
		it3->myVal = it1->myVal;

	typename T::iterator it2 = op2.integer.begin();
	for (it3 = sum.integer.begin(); it2 != op2.integer.end(); it2 = it2->next, it3 = it3->next)
		it3->myVal += it2->myVal;

	for (it3 = sum.integer.begin(); it3 != sum.integer.end()->prev; it3 = it3->next)
		if (it3->myVal > 9)
		{
			it3->myVal -= 10;
			((it3->next)->myVal)++;
		}

	if (it3->myVal == 0)
		sum.integer.erase(sum.integer.end()->prev);

	return sum;
} // end function operator+

// subtraction operator; HugeInteger< T > - HugeInteger< T >
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
	for (; it1 != integer.end(); it1 = it1->next, it3 = it3->next)
		it3->myVal = it1->myVal;

	typename T::iterator it2 = op2.integer.begin();

	for (it3 = difference.integer.begin(); it2 != op2.integer.end(); it2 = it2->next, it3 = it3->next) {
		if (it3->myVal >= it2->myVal)
			it3->myVal -= it2->myVal;
		else { //*it3 < *it2
			if ((it3->next)->myVal > 0) {
				it3->myVal += 10;
				((it3->next)->myVal)--;
			}
			else {//*(it3 + 1) <= 0
				it3->myVal += 10;
				it3 = it3->next;
				int i = 0;
				for (; it3 != difference.integer.end(); it3 = it3->next, i++) {
					it3->myVal += 9;
					if ((it3->next)->myVal > 0) {
						((it3->next)->myVal)--;
						break;
					}
				}
				for (i; i >= 0; i--, it3 = it3->prev);
			}
			it3->myVal -= it2->myVal;
		}
	}

	for (it3 = difference.integer.end()->prev; it3 != difference.integer.end(); it3 = it3->prev) {
		if (it3->myVal == 0)
			difference.integer.erase(it3);
		else {
			break;
		}
	}

	return difference;
} // end function operator-

// multiplication operator; HugeInteger< T > * HugeInteger< T >
template< typename T >
HugeInteger< T > HugeInteger< T >::operator*(HugeInteger& op2)
{
	HugeInteger zero;
	if (isZero() || op2.isZero())
		return zero;

	HugeInteger product(integer.size() + op2.integer.size());

	for (typename T::iterator it1 = op2.integer.begin(), it2 = product.integer.begin(); it1 != op2.integer.end(); it1 = it1->next, it2 = it2->next) {
		for (typename T::iterator it3 = integer.begin(), it4 = it2; it3 != integer.end(); it3 = it3->next, it4 = it4->next) {
			it4->myVal += it1->myVal * it3->myVal;
		}
	}

	typename T::iterator it1 = product.integer.begin();
	for (it1; it1 != product.integer.end(); it1 = it1->next) {
		if (it1->myVal >= 10) {
			it1->next->myVal += it1->myVal / 10;
			it1->myVal %= 10;
		}
	}

	for (it1 = product.integer.end()->prev; it1 != product.integer.end(); it1 = it1->prev) {
		if (it1->myVal == 0)
			product.integer.erase(it1);
		else
			break;
	}

	return product;
} // end function operator*

// division operator; HugeInteger< T > / HugeInteger< T > provided that the divisor is not equal to 0
template< typename T >
HugeInteger< T > HugeInteger< T >::operator/(HugeInteger& op2)
{
	HugeInteger zero;
	if (*this < op2)
		return zero;

	HugeInteger remainder(*this);
	HugeInteger buffer(integer.size());
	HugeInteger temp;

	int n = integer.size() - op2.integer.size();
	typename T::iterator it1 = op2.integer.begin();
	typename T::iterator it2 = buffer.integer.begin();
	for (int i = 0; i < n; ++i)
		it2 = it2->next;
	for (; it1 != op2.integer.end(); it1 = it1->next, it2 = it2->next)
		it2->myVal = it1->myVal;

	if (remainder < buffer)
		buffer.divideByTen();
	else
		n++;

	HugeInteger quotient(n);
	for (typename T::iterator it3 = quotient.integer.end()->prev; it3 != quotient.integer.end(); it3 = it3->prev) {
		while (buffer <= remainder) {
			temp = (remainder - (buffer));
			remainder = (temp.integer);
			(it3->myVal)++;
			if (remainder.isZero())
				return quotient;
		}
		buffer.divideByTen();
	}

	return quotient;
} // end function operator/

// modulus operator; HugeInteger< T > % HugeInteger< T > provided that the divisor is not equal to 0
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
	for (; it != integer.end(); it = it->next)
		if (it->myVal != 0)
			return false;

	return true;
}

// function that divides a HugeInteger by 10; shift a HugeInteger one position to the right
template< typename T >
void HugeInteger< T >::divideByTen()
{
	typename T::iterator it = integer.begin()->next;
	for (; it != integer.end(); it = it->next)
		(it->prev)->myVal = it->myVal;
	integer.erase(integer.end()->prev);
}

// function to help increment the integer
template< typename T >
void HugeInteger< T >::helpIncrement()
{
	typename T::iterator it = integer.begin();
	(it->myVal)++;
	typename T::iterator it2 = it;
	for (it2 = it2->next; it2 != integer.end(); it = it->next, it2 = it2->next)
		if (it->myVal == 10)
		{
			it->myVal = 0;
			(it2->myVal)++;
		}

	if ((it->myVal) == 10)
	{
		it->myVal = 0;
		integer.insert(integer.end(), 1);
	}
}

// function to help decrement the integer
template< typename T >
void HugeInteger< T >::helpDecrement()
{
	typename T::iterator it = integer.begin();
	for (; it->myVal == 0; it = it->next)
		it->myVal = 9;

	(it->myVal)--;

	if (!isZero() && integer.back() == 0)
		integer.erase(integer.end()->prev);
}

// overloaded output operator for class HugeInteger
template< typename T >
ostream& operator<<(ostream& output, HugeInteger< T > hugeInteger)
{
	typename T::iterator it = hugeInteger.integer.end()->prev;
	for (; it != hugeInteger.integer.begin()->prev; it = it->prev)
		if (it->myVal < 10)
			output << it->myVal;

	return output; // enables cout << x << y;
}

#endif