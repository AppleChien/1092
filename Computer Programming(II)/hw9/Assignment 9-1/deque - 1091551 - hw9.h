#ifndef DEQUE_H
#define DEQUE_H

#include "xutility.h" // include definition of class template ReverseIterator

// CLASS TEMPLATE DequeConstIterator
template< typename MyDeque >
class DequeConstIterator // iterator for nonmutable deque
{
private:
	using size_type = typename MyDeque::size_type;

public:
	using value_type = typename MyDeque::value_type;
	using difference_type = typename MyDeque::difference_type;
	using pointer = typename MyDeque::const_pointer;
	using reference = const value_type&;

	// construct with null pointer
	DequeConstIterator()
		: myOff(0),
		myCont(nullptr)
	{
	}

	// construct with offset off in *pDeque
	DequeConstIterator(size_type off, const MyDeque* pDeque)
		: myOff(off),
		myCont(pDeque)
	{
	}

	DequeConstIterator(const DequeConstIterator& right) // copy constructor
		: myOff(right.myOff),
		myCont(right.myCont)
	{
	}

	~DequeConstIterator() // destructor
	{
	}

	// const return avoids: ( a1 = a2 ) = a3
	const DequeConstIterator& operator=(const DequeConstIterator& right)
	{
		if (&right != this) // avoid self-assignment
		{
			myCont = right.myCont;
			myOff = right.myOff;
		}
		return *this; // enables x = y = z, for example
	}

	reference operator*() const
	{
		//      size_type block = myOff % ( 4 * myCont->mapSize ) / 4;
		size_type block = myCont->getBlock(myOff);
		size_type off = myOff % 4;
		return myCont->map[block][off];
	}

	pointer operator->() const
	{
		return &(operator*());
	}

	DequeConstIterator& operator++() // preincrement
	{
		++myOff;
		return *this;
	}

	DequeConstIterator operator++(int) // postincrement
	{
		DequeConstIterator tmp = *this;
		++* this;
		return tmp;
	}

	DequeConstIterator& operator--() // predecrement
	{
		--myOff;
		return *this;
	}

	DequeConstIterator operator--(int) // postdecrement
	{
		DequeConstIterator tmp = *this;
		--* this;
		return tmp;
	}

	// increment by integer
	DequeConstIterator& operator+=(const difference_type off)
	{
		myOff += off;
		return *this;
	}

	// return this + integer
	DequeConstIterator operator+(const difference_type off) const
	{
		DequeConstIterator tmp = *this;
		return tmp += off;
	}

	// decrement by integer
	DequeConstIterator& operator-=(const difference_type off)
	{
		return *this += -off;
	}

	// return this - integer
	DequeConstIterator operator-(const difference_type off) const
	{
		DequeConstIterator tmp = *this;
		return tmp -= off;
	}

	// return difference of iterators
	difference_type operator-(const DequeConstIterator& right) const
	{
		return (static_cast<difference_type>(this->myOff - right.myOff));
	}

	reference operator[](const difference_type off) const // subscript
	{
		return *(*this + off);
	}

	// test for iterator equality
	bool operator==(const DequeConstIterator& right) const
	{
		return this->myCont == right.myCont && this->myOff == right.myOff;
	}

	// test for iterator inequality
	bool operator!=(const DequeConstIterator& right) const
	{
		return !(*this == right);
	}

	// test if this < right
	bool operator<(const DequeConstIterator& right) const
	{
		return this->myOff < right.myOff;
	}

	// test if this > right
	bool operator>(const DequeConstIterator& right) const
	{
		return right < *this;
	}

	// test if this <= right
	bool operator<=(const DequeConstIterator& right) const
	{
		return !(right < *this);
	}

	// test if this >= right
	bool operator>=(const DequeConstIterator& right) const
	{
		return !(*this < right);
	}

	const MyDeque* myCont; // keep a pointer to deque
	size_type myOff;       // offset of element in deque
};


// CLASS TEMPLATE DequeIterator
template< typename MyDeque >
class DequeIterator : public DequeConstIterator< MyDeque >
{ // iterator for mutable deque
private:
	using size_type = typename MyDeque::size_type;
	using MyBase = DequeConstIterator< MyDeque >;

public:
	using value_type = typename MyDeque::value_type;
	using difference_type = typename MyDeque::difference_type;
	using pointer = typename MyDeque::pointer;
	using reference = value_type&;

	DequeIterator() // construct with null deque pointer
	{
	}

	DequeIterator(size_type off, const MyDeque* pDeque)
		: MyBase(off, pDeque) // construct with offset off in *pDeque
	{
	}

	reference operator*() const // return designated object
	{
		return const_cast<reference>(MyBase::operator*());
	}

	pointer operator->() const // return pointer to class object
	{
		return const_cast<pointer>(MyBase::operator->());
		//      return &( operator*() );
	}

	DequeIterator& operator++() // preincrement
	{
		MyBase::operator++();
		return *this;
	}

	DequeIterator operator++(int) // postincrement
	{
		DequeIterator tmp = *this;
		MyBase::operator++();
		return tmp;
	}

	DequeIterator& operator--() // predecrement
	{
		MyBase::operator--();
		return *this;
	}

	DequeIterator operator--(int) // postdecrement
	{
		DequeIterator tmp = *this;
		MyBase::operator--();
		return tmp;
	}

	// increment by integer
	DequeIterator& operator+=(const difference_type off)
	{
		MyBase::operator+=(off);
		return *this;
	}

	// return this + integer
	DequeIterator operator+(const difference_type off) const
	{
		DequeIterator tmp = *this;
		return tmp += off;
	}

	// decrement by integer
	DequeIterator& operator-=(const difference_type off)
	{
		MyBase::operator-=(off);
		return *this;
	}

	using MyBase::operator-; // return difference of iterators

	// return this - integer
	DequeIterator operator-(const difference_type off) const
	{
		DequeIterator tmp = *this;
		return tmp -= off;
	}

	reference operator[](const difference_type off) const // subscript
	{
		return const_cast<reference>(MyBase::operator[](off));
	}
};

// CLASS TEMPLATE DequeVal
template< typename Ty >
class DequeVal // base class for deque to hold data
{
public:
	using value_type = Ty;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;
	using MapPtr = Ty**;

	DequeVal() // initialize values
		: map(),
		mapSize(0),
		myOff(0),
		mySize(0)
	{
	}

	// determine block from offset
	size_type getBlock(size_type off) const
	{
		return off % (4 * mapSize) / 4;
		//      return ( off / 4 ) & ( mapSize - 1 );
	}

	MapPtr map;        // pointer to array of pointers to blocks
	size_type mapSize; // size of map array, zero or 2^N
	size_type myOff;   // offset of initial element
	size_type mySize;  // current length of sequence
};


// CLASS TEMPLATE deque
template< typename Ty >
class deque // circular queue of pointers to blocks
{
private:
	using MapPtr = Ty**;
	using ScaryVal = DequeVal< Ty >;

public:
	using value_type = Ty;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;

	using iterator = DequeIterator< ScaryVal >;
	using const_iterator = DequeConstIterator< ScaryVal >;

	using reverse_iterator = ReverseIterator< iterator >;
	using const_reverse_iterator = ReverseIterator< const_iterator >;

	// construct empty deque
	deque()
		: myData()
	{
	}

	// construct from count
	deque(size_type count)
		: myData()
	{
		if (count == 0)
		{
			myData.map = nullptr;
			myData.mapSize = 0;
		}
		else
		{
			myData.mapSize = 8;
			while (count > 4 * (myData.mapSize - 1))
				myData.mapSize *= 2;

			myData.map = new value_type * [myData.mapSize]();
			for (size_type i = 0; i <= (count - 1) / 4; i++)
				myData.map[i] = new value_type[4]();
		}
		myData.mySize = count;

	}

	// construct by copying right
	deque(const deque& right)
		: myData()
	{
		myData.mySize = right.myData.mySize;
		myData.myOff = right.myData.myOff;
		myData.mapSize = right.myData.mapSize;
		myData.map = new value_type * [myData.mapSize]();
		for (size_type i = 0; i < myData.mapSize; i++) {
			if (right.myData.map[i] != nullptr) {
				myData.map[i] = new value_type[4]();
				for (size_type j = 0; j < 4; j++) {
					myData.map[i][j] = right.myData.map[i][j];
				}
			}
		}
	}

	// destroy the deque
	~deque()
	{
		clear();
	}

	// Assigns new contents to the container, replacing its current contents,
	// and modifying its size accordingly.
	deque& operator=(const deque& right)
	{
		if (&right != this) // avoid self-assignment
		{
			myData.mySize = right.myData.mySize;
			myData.myOff = right.myData.myOff;
			myData.mapSize = right.myData.mapSize;
			myData.map = new value_type * [myData.mapSize]();
			for (size_type i = 0; i < myData.mapSize; i++) {
				if (right.myData.map[i] != nullptr) {
					myData.map[i] = new value_type[4]();
					for (size_type j = 0; j < 4; j++) {
						myData.map[i][j] = right.myData.map[i][j];
					}
				}
			}

		} // end outer if

		return *this; // enables right = y = z, for example
	} // end function operator=

	// return iterator for beginning of mutable sequence
	iterator begin()
	{
		return iterator(myData.myOff, &myData);
	}

	// return iterator for beginning of nonmutable sequence
	const_iterator begin() const
	{
		return const_iterator(myData.myOff, &myData);
	}

	// return iterator for end of mutable sequence
	iterator end()
	{
		return iterator(myData.myOff + myData.mySize, &myData);
	}

	// return iterator for end of nonmutable sequence
	const_iterator end() const
	{
		return const_iterator(myData.myOff + myData.mySize, &myData);
	}

	// return iterator for beginning of reversed mutable sequence
	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}

	// return iterator for beginning of reversed nonmutable sequence
	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(end());
	}

	// return iterator for end of reversed mutable sequence
	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}

	// return iterator for end of reversed nonmutable sequence
	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(begin());
	}

	// return iterator for beginning of nonmutable sequence
	const_iterator cbegin() const
	{
		return begin();
	}

	// return iterator for end of nonmutable sequence
	const_iterator cend() const
	{
		return end();
	}

	// return iterator for beginning of reversed nonmutable sequence
	const_reverse_iterator crbegin() const
	{
		return rbegin();
	}

	// return iterator for end of reversed nonmutable sequence
	const_reverse_iterator crend() const
	{
		return rend();
	}

	// return length of sequence
	size_type size() const
	{
		return myData.mySize;
	}

	// test if sequence is empty
	bool empty() const
	{
		return myData.mySize == 0;
	}

	const_reference operator[](size_type pos) const
	{
		return *(begin() + static_cast<difference_type>(pos));
	}

	reference operator[](size_type pos)
	{
		return *(begin() + static_cast<difference_type>(pos));
	}

	reference front()
	{
		return *begin();
	}

	const_reference front() const
	{
		return *begin();
	}

	reference back()
	{
		return *(end() - 1);
	}

	const_reference back() const
	{
		return *(end() - 1);
	}

	// insert val at where
	void insert(const_iterator where, const value_type& val)
	{
		if (myData.mySize == 0)
		{
			if (where == begin() && where == end())
			{
				if (myData.mapSize == 0)
				{
					myData.mapSize = 8;
					myData.map = new value_type * [myData.mapSize]();
					myData.map[7] = new value_type[4];
				}
				else
				{
					if (myData.map[myData.mapSize - 1] == nullptr)
						myData.map[myData.mapSize - 1] = new value_type[4];
				}
				myData.map[myData.mapSize - 1][3] = val;
				myData.myOff = myData.mapSize * 4 - 1;
			}
		}
		else
		{
			if (begin() <= where && where <= end())
			{
				// all elements before where move forward
				if (where <= begin() + myData.mySize / 2)
				{
					size_type newFront = (myData.myOff - 1) % (4 * myData.mapSize);
					if (newFront % 4 == 3 && myData.mySize >= 4 * (myData.mapSize - 1))
					{
						doubleMapSize();
						newFront = (myData.myOff - 1) % (4 * myData.mapSize);
					}

					if (myData.myOff % 4 == 0 && myData.map[newFront / 4] == nullptr) //如果myoff在位置為[][0]時往前移就要有新空間
						myData.map[newFront / 4] = new value_type[4];

					myData.myOff = newFront;
					size_type whereOff = where.myOff % (myData.mapSize * 4); //調整where.myoff 讓他<總大小
					size_type beforewhere = (whereOff == 0) ? myData.mapSize * 4 - 1 : whereOff - 1; //where的前一個位置

					while (newFront != beforewhere) {
						size_type next = (newFront + 1 == myData.mapSize * 4) ? 0 : newFront + 1;  //調整下一個位置
						myData.map[newFront / 4][newFront % 4] = myData.map[next / 4][next % 4]; //往前移
						newFront++;
						if (newFront == myData.mapSize * 4)
							newFront = 0;
					}
					myData.map[newFront / 4][newFront % 4] = val;

				}
				else  // all elements after (and at) where move backward
				{
					size_type newBack = (myData.myOff + myData.mySize) % (4 * myData.mapSize);
					if (newBack % 4 == 0 && myData.mySize >= 4 * (myData.mapSize - 1))
					{
						doubleMapSize();
						newBack = myData.myOff + myData.mySize;
					}

					myData.myOff %= (4 * myData.mapSize); //調整myoff
					if ((myData.myOff + myData.mySize - 1) % 4 == 3 && myData.map[newBack / 4] == nullptr)//如果myoff在位置為[][3]時往後移就要有新空間
						myData.map[newBack / 4] = new value_type[4];

					size_type whereOff = where.myOff % (myData.mapSize * 4); //調整where.myoff

					while (newBack != whereOff) {
						size_type next = (newBack - 1 == -1) ? myData.mapSize * 4 - 1 : newBack - 1; //調整下一個
						myData.map[(newBack) / 4][(newBack) % 4] = myData.map[(next) / 4][(next) % 4]; //往後移
						newBack--;
						if (newBack == -1)
							newBack = myData.mapSize * 4 - 1;
					}
					myData.map[newBack / 4][newBack % 4] = val;

				}
			}
		}

		++myData.mySize;
	}

	// erase element at where
	void erase(const_iterator where)
	{
		if (myData.mySize > 0 && begin() <= where && where < end())
		{
			if (myData.mySize == 1 && begin() == where)
			{
				myData.myOff = 0;
				myData.mySize = 0;
			}
			else
			{
				size_type myOff = myData.myOff % (myData.mapSize * 4); //調整myoff
				size_type whereoff = where.myOff % (myData.mapSize * 4); //調整whereoff
			   // all elements before where move backward
				if (where < begin() + myData.mySize / 2)
				{
					//從whereoff到myoff往後一格
					while (whereoff != myOff) {
						size_type next = (whereoff == 0) ? myData.mapSize * 4 - 1 : whereoff - 1; //調整下一個
						myData.map[(whereoff) / 4][(whereoff) % 4] = myData.map[(next) / 4][(next) % 4];
						whereoff--;
						if (whereoff == -1)
							whereoff = myData.mapSize * 4 - 1;
					}
					++myData.myOff;

				}
				else // all elements after where move forward
				{
					size_type end = ((myOff + myData.mySize) >= myData.mapSize * 4) ? (myOff + myData.mySize - 1) % (myData.mapSize * 4) : myOff + myData.mySize - 1; //最後的前一格
						//從whereoff到end往前一格
					while (whereoff != end) {
						size_type next = (whereoff + 1 == myData.mapSize * 4) ? 0 : whereoff + 1; //調整下一個
						myData.map[(whereoff) / 4][(whereoff) % 4] = myData.map[next / 4][next % 4];
						whereoff++;
						if (whereoff == myData.mapSize * 4)
							whereoff = 0;
					}

				}

				--myData.mySize;
			}
		}
	}

	// erase all
	void clear()
	{
		if (myData.mapSize > 0)
		{
			for (size_type i = 0; i < myData.mapSize; i++)
				if (myData.map[i] != nullptr)
					delete[] myData.map[i];
			delete[] myData.map;

			myData.mapSize = 0;
			myData.mySize = 0;
			myData.myOff = 0;
			myData.map = MapPtr();
		}
	}

private:

	// determine block from offset
	size_type getBlock(size_type off) const
	{
		return myData.getBlock(off);
		//      return ( ( myData.off / 4 ) & ( myData.mapSize - 1 ) );
	}

	void doubleMapSize()
	{
		if (myData.mapSize > 0)
		{
			size_t tempSize = myData.mapSize * 2;
			MapPtr temp = new value_type * [tempSize]();
			int i = myData.myOff / 4; //舊的map位置
			int j = i; //新的map位置
			int count = 0;
			while (myData.map[i] != nullptr && count != myData.mapSize)
			{
				temp[j] = myData.map[i]; //舊的複製到新的
				i++;
				j++;
				count++;
				if (i == myData.mapSize) //舊的走到底從0開始
					i = 0;
			}
			delete[] myData.map;
			myData.map = temp;
			myData.mapSize = tempSize;
		}
	}

	ScaryVal myData;
};

// test for deque equality
template< typename Ty >
bool operator==(const deque< Ty >& left, const deque< Ty >& right)
{
	if (left.size() != right.size())
		return false;
	else {
		typename deque< Ty >::const_iterator it1 = left.cbegin();
		typename deque< Ty >::const_iterator it2 = right.cbegin();
		for (it1; it1 != left.cend(); ++it1, ++it2) {
			if (*it1 != *it2)
				return false;
		}
		return true;
	}

}

#endif