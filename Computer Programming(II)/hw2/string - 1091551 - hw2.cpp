#include <iostream>
using std::cout;
using std::exit;

#include "string.h" // include definition of class String

string::string()
	: bx(),
	mySize(0),
	myRes(15)
{
}

string::string(const char* const ptr, const size_type count)
	: bx(),
	mySize(0),
	myRes(15)
{
	if (count > 15) {
		mySize = count;
		myRes = count / 16 * 16 + 15;
		value_type* array = new value_type[myRes](); //value_type=char
		for (int a = 0;a < count;a++) {
			array[a] = ptr[a];
		}
		bx.ptr = array;
	}
	else { //count<=15
		mySize = count;
		for (int a = 0;a < count;a++) {
			bx.buf[a] = ptr[a];
		}
	}

	/*myRes = count / 16 * 16 + 15;
	mySize = count;
	if (count > 15) {
		value_type* array = new value_type[myRes]();
		bx.ptr = array;
	}
	for(int a=0;a<count;a++
		myPtr()[a]=ptr[a];*/
}

string::string(const size_type count, const char ch)
	: bx(),
	mySize(0),
	myRes(15)
{
	if (count > 15) {
		mySize = count;
		myRes = count / 16 * 16 + 15;
		value_type* array = new value_type[myRes](); //value_type=char
		for (int a = 0;a < count;a++) {
			array[a] = ch;
		}
		bx.ptr = array;
	}
	else { //count<=15
		mySize = count;
		for (int a = 0;a < count;a++) {
			bx.buf[a] = ch;
		}
	}
}

string::string(const string& right)
	: bx(),
	mySize(0),
	myRes(15)
{
	mySize = right.mySize;

	if (right.myRes > myRes)
	{
		myRes = (right.size() / 16) * 16 + 15;
		bx.ptr = new char[myRes + 1];
		for (int i = 0; i < mySize; i++)
			bx.ptr[i] = right.bx.ptr[i];
	}
	else { //right.myRes <= myRes
		for (int i = 0; i < mySize; i++)
			bx.buf[i] = right.bx.buf[i];
	}
}

string::~string()
{
	if (myRes > 15)
		delete[] bx.ptr;
}

string::value_type* string::myPtr()
{
	if (myRes < 16)
		return bx.buf;
	else
		return bx.ptr;
}

const string::value_type* string::myPtr() const
{
	if (myRes < 16)
		return bx.buf;
	else
		return bx.ptr;
}

string& string::assign(const string& right)
{
	if (right.mySize <= myRes)
	{
		mySize = right.mySize;
		for (int i = 0; i < right.mySize; i++)
			myPtr()[i] = right.myPtr()[i];
	}
	else { //right.mySize > myRes
		int newRes;
		
		if (myRes > 15){
			delete[] myPtr();
		}
		if ((right.mySize / 16) * 16 + 15 > myRes * 3 / 2){
			newRes = (right.mySize / 16) * 16 + 15;
		}
		else{
			newRes = myRes * 3 / 2;
		}
		mySize = right.mySize;
		myRes = newRes;
		bx.ptr = new value_type[newRes + 1];
		for (int i = 0; i < right.mySize; i++)
			myPtr()[i] = right.myPtr()[i];
	}
	return *this;
}

string::iterator string::insert(const_iterator where, const char ch)
{
	if (where >= myPtr() && where <= myPtr() + mySize) //myPtr=array材竚
	{
		if (mySize == 0){
			myPtr()[0] = ch;
			mySize++;
			return myPtr();
		}

		if (mySize == myRes){
			if (mySize > 15) {
				iterator tempPtr = bx.ptr;
				int newRes;
				if (myRes == 31){
					newRes = 47;
				}
				else{
					newRes = myRes * 3 / 2;
				}
				int postion = where - bx.ptr;
				bx.ptr = new char[newRes + 1];

				int j = 0, i = 0;
				for (int j = 0; j < mySize; j++){
					if (i == postion){
						bx.ptr[i] = ch;
						i++;
						j--;
						continue;
					}
					bx.ptr[i] = tempPtr[j];
					i++;
				}
				if (postion == mySize)
					bx.ptr[mySize] = ch;
				delete[] tempPtr;
				mySize++;
				myRes = newRes;
			}
			else { //mySize<=15
				char temp[15];
				int postion = where - bx.buf;
				for (int i = 0; i < 15; i++)
					temp[i] = myPtr()[i];
				int newRes = 31;

				bx.ptr = new char[newRes + 1];

				iterator i = bx.ptr;
				int j = 0;
				while (j < 15)
				{
					if (i - bx.ptr == postion){
						*i = ch;
						i++;
						continue;
					}
					*i = temp[j];
					i++;
					j++;
				}
				if (postion == mySize){
					bx.ptr[mySize] = ch;
				}
				mySize++;
				myRes = newRes;
			}
		}
		else { //mySizeぃ单myRes(mySize<myRes)
			int i = mySize, postion = where - myPtr();
			for (i; i >= postion; i--){ //position常┕簿
				myPtr()[i + 1] = myPtr()[i];
			}
			myPtr()[i + 1] = ch;
			mySize++;
		}
		//myPtr()[mySize] = '\0';
		return myPtr();
	}
	else
		return iterator(nullptr);
}

string::iterator string::erase(const_iterator where)
{
	if (where >= myPtr() && where < myPtr() + mySize) //myPtr=array材竚
	{
		for (int a = where - myPtr();a < mySize;a++) {
			myPtr()[a] = myPtr()[a + 1]; //where秨﹍程常┕玡簿
		}
		mySize -= 1;
		return myPtr();
	}
	else
		return iterator(nullptr);
}

void string::clear()
{
	mySize = 0;
	myPtr()[0] = value_type();
}

string::iterator string::begin()
{
	return myPtr();
}

string::const_iterator string::begin() const
{
	return const_iterator(myPtr());
}

string::iterator string::end()
{
	return myPtr() + static_cast<difference_type>(mySize);
}

string::const_iterator string::end() const
{
	return const_iterator(myPtr() + static_cast<difference_type>(mySize));
}

string::reference string::element(const size_type off)
{
	if (off > mySize)
	{
		cout << "string subscript out of range\n";
		exit(1);
	}

	return myPtr()[off];
}

string::const_reference string::element(const size_type off) const
{
	if (off > mySize)
	{
		cout << "string subscript out of range\n";
		exit(1);
	}

	return myPtr()[off];
}

string::reference string::front()
{
	return myPtr()[0];
}

string::const_reference string::front() const
{
	return myPtr()[0];
}

string::reference string::back()
{
	return myPtr()[mySize - 1];
}

string::const_reference string::back() const
{
	return myPtr()[mySize - 1];
}

const char* string::c_str() const
{
	return myPtr();
}

string::size_type string::size() const
{
	return mySize;
}

string::size_type string::capacity() const
{
	return myRes;
}

bool string::empty() const
{
	return mySize == 0;
}