// string class member-function definitions.

#include <iostream>
using std::cout;

#include "string.h" // string class definition

string::string()
	: myData()
{
}

string::string(const char* const ptr, const size_type count)
	: myData()
{
	myData.myRes = count / 16 * 16 + 15;
	myData.mySize = count;
	if (count > 15) {
		value_type* array = new value_type[myData.myRes]();
		myData.bx.ptr = array;
	}
	for (int a = 0;a < count;a++)
		myData.myPtr()[a] = ptr[a];

}

string::string(const size_type count, const char ch)
	: myData()
{
	if (count > 15) {
		myData.mySize = count;
		myData.myRes = count / 16 * 16 + 15;
		value_type* array = new value_type[myData.myRes](); //value_type=char
		for (int a = 0;a < count;a++) {
			array[a] = ch;
		}
		myData.bx.ptr = array;
	}
	else { //count<=15
		myData.mySize = count;
		for (int a = 0;a < count;a++) {
			myData.bx.buf[a] = ch;
		}
	}

}

string::string(const string& right)
	: myData()
{
	myData.mySize = right.myData.mySize;

	if (right.myData.myRes > myData.myRes)
	{
		myData.myRes = (right.size() / 16) * 16 + 15;
		myData.bx.ptr = new char[myData.myRes + 1];
		for (int i = 0; i < myData.mySize; i++)
			myData.bx.ptr[i] = right.myData.bx.ptr[i];
	}
	else { //right.myRes <= myRes
		for (int i = 0; i < myData.mySize; i++)
			myData.bx.buf[i] = right.myData.bx.buf[i];
	}

}

string::~string()
{
	if (myData.myRes > 15)
		delete[] myData.bx.ptr;
}

string& string::operator=(const string& right)
{
	if (this != &right)
	{
		if (right.myData.mySize <= myData.myRes)
		{
			myData.mySize = right.myData.mySize;
			for (int i = 0; i < right.myData.mySize; i++)
				myData.myPtr()[i] = right.myData.myPtr()[i];
		}
		else { //right.mySize > myRes
			int newRes;

			if (myData.myRes > 15) {
				delete[] myData.myPtr();
			}
			if ((right.myData.mySize / 16) * 16 + 15 > myData.myRes * 3 / 2) {
				newRes = (right.myData.mySize / 16) * 16 + 15;
			}
			else {
				newRes = myData.myRes * 3 / 2;
			}
			myData.mySize = right.myData.mySize;
			myData.myRes = newRes;
			myData.bx.ptr = new value_type[newRes + 1];
			for (int i = 0; i < right.myData.mySize; i++)
				myData.myPtr()[i] = right.myData.myPtr()[i];
		}

	}

	return *this;
}

string& string::operator=(const char* const ptr)
{
	size_t count = 0; //要放幾個字
	while (ptr[count] != '\0')
	{
		count++;
	}
	myData.mySize = count;
	if (count <= myData.myRes)
	{
		myData.myPtr()[count] = '\0';
	}
	else { //count > myData.myRes
		size_t newRes;

		if (myData.myRes > 15) {
			delete[] myData.myPtr();
		}
		if ((count / 16) * 16 + 15 > myData.myRes * 3 / 2) {
			newRes = (count / 16) * 16 + 15;
		}
		else {
			newRes = myData.myRes * 3 / 2;
		}
		myData.myRes = newRes;
		myData.bx.ptr = new value_type[newRes + 1];
	}
	for (size_t i = 0; i < count; i++)
		myData.myPtr()[i] = ptr[i];
	return *this;
}

string& string::erase(size_t off, size_t count)
{
	if (off < myData.mySize)
	{
		size_t this_size = size();
		for (size_t i = off + count; i < this_size; i++)
		{
			myData.myPtr()[i - count] = myData.myPtr()[i];
		}
		myData.mySize = myData.mySize - count;
		myData.myPtr()[this_size - count] = '\0';
	}
	return *this;
}

void string::clear()
{
	myData.mySize = 0;
	myData.myPtr()[0] = value_type();
}

string::iterator string::begin()
{
	return iterator(myData.myPtr());
}

string::const_iterator string::begin() const
{
	return const_iterator(myData.myPtr());
}

string::iterator string::end()
{
	return iterator(myData.myPtr() + static_cast<difference_type>(myData.mySize));
}

string::const_iterator string::end() const
{
	return const_iterator(myData.myPtr() + static_cast<difference_type>(myData.mySize));
}

string::reference string::operator[](size_type off)
{
	// check for off out-of-range error
	if (off > myData.mySize)
	{
		cout << "\nstring subscript out of range\n";
		system("pause");
		exit(1); // terminate program; off out of range
	}

	return myData.myPtr()[off]; // returns copy of this element
}

string::const_reference string::operator[](size_type off) const
{
	// check for off out-of-range error
	if (off > myData.mySize)
	{
		cout << "\nstring subscript out of range\n";
		system("pause");
		exit(1); // terminate program; off out of range
	}

	return myData.myPtr()[off]; // returns copy of this element
}

string::const_pointer string::data() const
{
	return myData.myPtr();
}

string::size_type string::size() const
{
	return myData.mySize;
}

string::size_type string::find(char ch, size_type off) const
{
	for (size_t i = off;i < myData.mySize;i++) {
		if (myData.myPtr()[i] == ch)
			return i;
	}
	return string::npos;
}

string string::substr(size_type off, size_type count) const
{//從off開始後count位
	size_t number = count; //要抽幾個字
	if ((begin() + off + count - 1) > end()) { //選取範圍過大
		number = size() - off;
	}
	string array;
	array.myData.mySize = count;

	for (int i = off, j = 0;i < off + number;i++, j++)
		array[j] = myData.myPtr()[i];

	return array;
}

// compare [ 0, size() ) with right for equality
bool string::equal(const string& right) const
{
	if (myData.mySize != right.myData.mySize)
		return false;
	else {
		for (int i = 0;i < myData.mySize;i++) {
			if (myData.myPtr()[i] != right.myData.myPtr()[i])
				return false;
			else {
				if (i != myData.mySize - 1)
					i++;
				else
					return true;
			}
		}
	}
}

bool operator==(const string& left, const string& right)
{
	return left.equal(right);
	//   return ( lhs.compare( rhs ) == 0 );
}

bool operator!=(const string& left, const string& right)
{
	return !left.equal(right);
}

ostream& operator<<(ostream& ostr, string& str)
{
	for (size_t i = 0; i < str.size(); i++)
		ostr << str.data()[i];

	return ostr; // enables cout << x << y;
}