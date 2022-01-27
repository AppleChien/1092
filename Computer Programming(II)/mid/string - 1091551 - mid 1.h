// string internal header

#ifndef STRING
#define STRING

// CLASS StringVal
template < typename ValueType >
class StringVal
{
public:
	using value_type = ValueType;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;

	StringVal()
		: bx(),
		mySize(0),
		myRes(15)
	{
	}

	value_type* myPtr()
	{
		if (myRes < 16)
			return bx.buf;
		else
			return bx.ptr;
	}

	const value_type* myPtr() const
	{
		if (myRes < 16)
			return bx.buf;
		else
			return bx.ptr;
	}

	union Bxty // storage for small buffer or pointer to larger one
	{
		value_type buf[16];
		pointer ptr;
	} bx;

	size_type mySize; // current length of string
	size_type myRes;  // current storage reserved for string
};

class string // null-terminated transparent array of elements
{
	using ScaryVal = StringVal< char >;

public:
	using value_type = char;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;

	using iterator = value_type*;
	using const_iterator = const value_type*;

	// empty string constructor (default constructor)
	// Constructs an empty string, with a length of zero characters.
	string()
		: myData()
	{
	}

	// String destructor
	// Destroys the string object.
	// Deallocates all the storage capacity allocated by the string.
	~string()
	{
		if (myData.myRes > 15)
			delete[] myData.bx.ptr;
	}

	// Erases the contents of the string, which becomes an empty string
	// (with a length of 0 characters).
	void clear()
	{
		myData.mySize = 0;
		myData.myPtr()[0] = value_type();
	}

	// Returns an iterator pointing to the first character of the string.
	iterator begin()
	{
		return iterator(myData.myPtr());
	}

	// Returns an iterator pointing to the first character of the string.
	const_iterator begin() const
	{
		return const_iterator(myData.myPtr());
	}

	// Returns an iterator pointing to the past-the-end character of the string.
	// The past-the-end character is a theoretical character
	// that would follow the last character in the string.
	// It shall not be dereferenced.
	// If the object is an empty string, this function returns the same as string::begin.
	iterator end()
	{
		return iterator(myData.myPtr() + static_cast<difference_type>(myData.mySize));
	}

	// Returns an iterator pointing to the past-the-end character of the string.
	// The past-the-end character is a theoretical character
	// that would follow the last character in the string.
	// It shall not be dereferenced.
	// If the object is an empty string, this function returns the same as string::begin.
	const_iterator end() const
	{
		return const_iterator(myData.myPtr() + static_cast<difference_type>(myData.mySize));
	}

	// Returns a const_iterator pointing to the first character of the string.
	const_iterator cbegin() const
	{
		return begin();
	}

	// Returns a const_iterator pointing to the past-the-end character of the string.
	// If the object is an empty string, this function returns the same as string::cbegin.
	// The value returned shall not be dereferenced.
	const_iterator cend() const
	{
		return end();
	}

	// Returns a reference to the character at position pos in the string.
	reference operator[](const size_type off)
	{
		if (off > myData.mySize)
		{
			cout << "string subscript out of range\n";
			exit(1);
		}

		return myData.myPtr()[off];
	}

	// Returns a reference to the character at position pos in the string.
	const_reference operator[](const size_type off) const
	{
		if (off > myData.mySize)
		{
			cout << "string subscript out of range\n";
			exit(1);
		}

		return myData.myPtr()[off];
	}

	// Appends character ch to the end of the string, increasing its length by one.
	void push_back(char ch)
	{
		resize(myData.mySize + 1);
		myData.myPtr()[myData.mySize - 1] = ch;
	}

	// Erases the last character of the string,
	// effectively reducing its length by one.
	void pop_back()
	{
		if (myData.mySize > 0)
			--myData.mySize;
	}

	// Returns a reference to the first character of the string.
	// This function shall not be called on empty strings.
	reference front()
	{
		return myData.myPtr()[0];
	}

	// Returns a reference to the first character of the string.
	// This function shall not be called on empty strings.
	const_reference front() const
	{
		return myData.myPtr()[0];
	}

	// Returns a reference to the last character of the string.
	// This function shall not be called on empty strings.
	reference back()
	{
		return myData.myPtr()[myData.mySize - 1];
	}

	// Returns a reference to the last character of the string.
	// This function shall not be called on empty strings.
	const_reference back() const
	{
		return myData.myPtr()[myData.mySize - 1];
	}

	// Returns a pointer to an array that contains a null-terminated sequence of characters
	// (i.e., a C-string) representing the current value of the string object.
	const char* c_str() const
	{
		return myData.myPtr();
	}

	// Returns the length of the string, in terms of bytes.
	// This is the number of actual bytes that conform the contents of the string,
	// which is not necessarily equal to its storage capacity.
	size_type size() const
	{
		return myData.mySize;
	}

	// Resizes the string to a length of "newSize" characters.
	// If "newSize" is smaller than the current string length,
	// the current value is shortened to its first "newSize" character,
	// removing the characters beyond the "newSize"th.
	// If "newSize" is greater than the current string length,
	// the current content is extended by inserting at the end
	// as many characters as needed to reach a size of "newSize".
	// The new elements are initialized as copies of ch.
	void resize(const size_type newSize, const char ch = char())
	{
		// determine new length, padding with ch elements as needed
		if (newSize > myData.mySize)
		{
			if (newSize > myData.myRes)
			{
				size_type newMyRes = myData.myRes * 3 / 2;
				if (newMyRes < (newSize / 16) * 16 + 15)
					newMyRes = (newSize / 16) * 16 + 15;
				
				value_type* array = new value_type[newMyRes]();
				pointer i = myData.myPtr();
				pointer j = array;
				for (; i != myData.myPtr() + myData.mySize; ++i, ++j) {
					*j = *i;
				}
				pointer k = array + myData.mySize;
				for (; k != array + newSize; ++k) {
					*k = ch;
				}
				myData.bx.ptr = array;
				myData.mySize = newSize;
				myData.myRes = newMyRes;
			}
			else {//newSize <= myData.myRes	
				pointer i = myData.myPtr() + myData.mySize;
				for (; i != myData.myPtr() + newSize; ++i) {
					*i = ch;
				}
				myData.mySize = newSize;
			}
		}
		else {//newSize <= myData.mySize
			myData.mySize = newSize;
			/*for (int i = 0; i < myData.mySize; i++) {
				myData.myPtr()[i] = ch;                      //deleted
			}*/
		}
	}

	// Returns the size of the storage space currently allocated for the string,
	// expressed in terms of bytes.
	// This capacity is not necessarily equal to the string length.
	// It can be equal or greater, with the extra space allowing the object
	// to optimize its operations when new characters are added to the string.
	size_type capacity() const
	{
		return myData.myRes;
	}

	// Returns whether the string is empty (i.e. whether its length is 0).
	bool empty() const
	{
		return myData.mySize == 0;
	}

private:
	ScaryVal myData;
};

#endif // STRING