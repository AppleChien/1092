#include "vector.h" // include definition of class vector 

// empty container constructor (default constructor)
// Constructs an empty container, with no elements.
vector::vector()
   : myFirst(),
     myLast(),
     myEnd()
{
}

// fill constructor
// Constructs a container with "count" elements.
// Each element is initialized as 0.
vector::vector( const size_type count )
	:myFirst(),
	myLast(),
	myEnd()
{
	int* array; //自己建一個新的動態陣列
	array = new int[count];
	for (int i = 0;i < count;i++) { //每一項填入0
		array[i] = 0;
	}
	myFirst = &array[0]; //myFirst指向第一個位置
	myEnd = myFirst + count; //myLast和myEnd指向陣列外面的位置
	myLast = myEnd;
}

// copy constructor
// Constructs a container with a copy of each of the elements in "right",
// in the same order.
vector::vector( const vector &right )  
	:myFirst(),
	myLast(),
    myEnd()
{
	int rightSize = right.myLast - right.myFirst;
	int rightCapacity = right.myEnd - right.myFirst;

	myFirst = new int[rightSize]();
	myEnd = &myFirst[rightSize];
	int* a = myFirst;

	for (int i = 0;i < rightSize;i++) { //開始一個一個copy
		*a = right.myFirst[i];
		a++; //a指向copy完的後一個位置==myLast指向的位置
	}
	myLast = a;
}

// Vector destructor
// Destroys the container object.
// Deallocates all the storage capacity allocated by the vector.
vector::~vector()
{
   if( myFirst != nullptr )
      delete[] myFirst;
}

// The vector is extended by inserting a new element before the element
// at the specified position, effectively increasing the container size by one.
// This causes an automatic reallocation of the allocated storage space
// if and only if the new vector size surpasses the current vector capacity.
// Relocates all the elements that were after "where" to their new positions.
vector::iterator vector::insert( const_iterator where, const value_type &val )
{
	int* i;
	if (myFirst == nullptr && myLast == nullptr && myEnd == nullptr) { //capacity=0
		myFirst = new int[1]{ val }; //設大小為1 值為val
		myEnd = myLast = &myFirst[1];
		return myFirst;
	}
	else {
		if (size() < capacity()) {
			if (where == myLast) { //要改的值剛好在myLast的位置
				*myLast = val;
				myLast += 1;
			}
			else { //要改的值沒有在myLast的位置(myLast以前)
				for (i = myLast - 1; i >= where; i--) { //where以後的值都往後移1格
					*(i + 1) = *i;
				}
				*(i + 1) = val;
				myLast += 1;
			}
		}
		else { //size=capacity
			int* tempPtr, * j;
			int position = where - myFirst;
			tempPtr = myFirst;
			int a = capacity() * 3 / 2;
			if (capacity() == 1) { //因為1*1.5還是=1
				a = 2;
			}
			myFirst = new int[a]; //格子增加後的大小
			myEnd = &myFirst[a]; //myEnd位置

			i = myFirst;
			j = tempPtr;

			if (where == myLast) { //要改的值剛好在myLast的位置
				while (j < myLast) {
					*i = *j;
					i++;
					j++;
				}
				*i = val;
				myLast = i + 1;
			}
			else { //要改的值沒有在myLast的位置(myLast以前)
				while (j < myLast) //tempPtr在myLast前
				{
					if (i - myFirst == position) { //新的myFirst跟where在不同陣列上
						*i = val;
						i++;
						continue;
					}
					*i = *j;
					i++;
					j++;
				}
				myLast = i;
			}
			delete[] tempPtr;
		}
		return myFirst;
	}
}

// overloaded assignment operator
// Assigns new contents to the container, replacing its current contents,
// and modifying its size accordingly.
// Copies all the elements from "right" into the container
// (with "right" preserving its contents).
vector& vector::assign( const vector &right )
{
   if( this != &right ) // avoid self-assignment
   {
	   size_type rightSize, rightCapacity;
	   rightSize = right.myLast - right.myFirst;
	   rightCapacity = right.myEnd - right.myFirst;

	   if (rightSize > capacity() && rightSize <= capacity() * 3 / 2) {
		   int* tempPtr, * j;
		   tempPtr = myFirst;
		   int a = capacity() * 3 / 2;
		   if (capacity() == 1) { //因為1*1.5還是=1
			   a = 2;
		   }
		   myFirst = new int[a](); //格子增加後的大小
		   myEnd = &myFirst[a]; //myEnd位置
		   j = myFirst;
		   for (int i = 0; i < rightSize; i++) { //將值assign進去
			   *j = right.myFirst[i];
			   j++;
		   }
		   myLast = j;
		   delete[] tempPtr;
	   }
	   else if (rightSize > capacity() * 3 / 2) {
		   int* tempPtr, * j;
		   tempPtr = myFirst;
		   myFirst = new int[rightSize](); //格子增加後的大小
		   myEnd = myLast = &myFirst[rightSize]; //myEnd跟myLast位置(陣列外)
		   j = myFirst;
		   for (int i = 0; i < rightSize; i++) { //將值assign進去
			   *j = right.myFirst[i];
			   j++;
		   }
		   delete[] tempPtr;
	   }
	   else if (rightSize <= capacity()) {
		   int* j = myFirst;
		   for (int i = 0; i < rightSize; i++) { //將值assign進去
			   *j = right.myFirst[i];
			   j++;
		   }
		   myLast = j;
	   }
   }

   return *this; // enables x = y = z, for example
}

// Removes from the vector a single element (where).
// This effectively reduces the container size by one, which is destroyed.
// Relocates all the elements after the element erased to their new positions.
vector::iterator vector::erase( const_iterator where )
{
	if (where == myLast) { //要刪掉的值剛好在myLast的位置
		myLast -= 1;
	}
	else { //要刪掉的值沒有在myLast的位置(myLast以前)
		int* i = myFirst;
		while (i != where) //如果i不在where的位置
			i++; //繼續找
		for (i;i < myLast;i++) { //找到where後一個一個往前移
			*i = *(i + 1);
		}
		myLast -= 1;
	}
	return myFirst;
}

// Removes all elements from the vector (which are destroyed),
// leaving the container with a size of 0.
// A reallocation is not guaranteed to happen,
// and the vector capacity is not guaranteed to change due to calling this function.
void vector::clear() // erase all
{
   myLast = myFirst;
}

// Returns an iterator pointing to the first element in the vector.
// If the container is empty, the returned iterator value shall not be dereferenced.
vector::iterator vector::begin()
{
   return myFirst;
}

// Returns an iterator pointing to the first element in the vector.
// If the container is empty, the returned iterator value shall not be dereferenced.
vector::const_iterator vector::begin() const
{
   return const_iterator( myFirst );
}

// Returns an iterator referring to the past-the-end element in the vector container.
// The past-the-end element is the theoretical element
// that would follow the last element in the vector.
// It does not point to any element, and thus shall not be dereferenced.
// If the container is empty, this function returns the same as vector::begin.
vector::iterator vector::end()
{
   return myLast;
}

// Returns an iterator referring to the past-the-end element in the vector container.
// The past-the-end element is the theoretical element
// that would follow the last element in the vector.
// It does not point to any element, and thus shall not be dereferenced.
// If the container is empty, this function returns the same as vector::begin.
vector::const_iterator vector::end() const
{
   return const_iterator( myLast );
}

// Returns a const_iterator pointing to the first element in the container.
// If the container is empty, the returned iterator value shall not be dereferenced.
vector::const_iterator vector::cbegin() const
{
   return begin();
}

// Returns a const_iterator pointing to the past-the-end element in the container.
// If the container is empty, this function returns the same as vector::cbegin.
// The value returned shall not be dereferenced.
vector::const_iterator vector::cend() const
{
   return end();
}

// Returns whether the vector is empty (i.e. whether its size is 0).
bool vector::empty() const
{
   return myFirst == myLast;
}

// Returns the number of elements in the vector.
// This is the number of actual objects held in the vector,
// which is not necessarily equal to its storage capacity.
vector::size_type vector::size() const
{
   return static_cast< size_type >( myLast - myFirst );
}

// Returns the size of the storage space currently allocated for the vector,
// expressed in terms of elements.
// This capacity is not necessarily equal to the vector size.
// It can be equal or greater, with the extra space allowing to accommodate
// for growth without the need to reallocate on each insertion.
vector::size_type vector::capacity() const
{
   return static_cast< size_type >( myEnd - myFirst );
}

// Returns a reference to the first element in the vector.
// Calling this function on an empty container causes undefined behavior.
vector::value_type& vector::front()
{
   return *myFirst;
}

// Returns a reference to the first element in the vector.
// Calling this function on an empty container causes undefined behavior.
const vector::value_type& vector::front() const
{
   return *myFirst;
}

// Returns a reference to the last element in the vector.
// Calling this function on an empty container causes undefined behavior.
vector::value_type& vector::back()
{
   return myLast[ -1 ];
}

// Returns a reference to the last element in the vector.
// Calling this function on an empty container causes undefined behavior.
const vector::value_type& vector::back() const
{
   return myLast[ -1 ];
}