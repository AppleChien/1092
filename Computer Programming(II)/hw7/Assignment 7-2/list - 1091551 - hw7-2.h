// list standard header

#ifndef LIST
#define LIST

template< typename ValueType >
struct ListNode // list node
{
	ListNode* next;  // successor node, or first element if head
	ListNode* prev;  // predecessor node, or last element if head
	ValueType myVal; // the stored value, unused if head
};


// CLASS TEMPLATE ListVal
template< typename Ty >
class ListVal
{
public:
	using node = ListNode< Ty >;
	using nodePtr = node*;

	using value_type = Ty;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;

	ListVal() // initialize data
		: myHead(),
		mySize(0)
	{
	}

	nodePtr myHead; // pointer to head node
	size_type mySize; // number of elements
};


// CLASS TEMPLATE list
template< typename Ty >
class list // bidirectional linked list
{
	using node = ListNode< Ty >;
	using nodePtr = node*;
	using ScaryVal = ListVal< Ty >;

public:
	using value_type = Ty;
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;

	using iterator = node*;
	using const_iterator = const node*;

	// empty container constructor (default constructor)
	// Constructs an empty container, with no elements.
	list()
		: myData()
	{
		myData.myHead = new node;
		myData.myHead->myVal = Ty();
		myData.myHead->prev = myData.myHead->next = myData.myHead;
	}

	// fill constructor
	// Constructs a container with "count" elements.
	// Each element is initialized as 0.
	list(size_type count) // construct list from count * Ty()
		: myData()
	{
		myData.myHead = new node;
		myData.myHead->myVal = Ty();
		myData.myHead->prev = myData.myHead->next = myData.myHead;

		if (count > 0)
			for (size_type i = 0; i < count; ++i)
				insert(end(), Ty());
	}

	// copy constructor
	// Constructs a container with a copy of each of the elements in "right",
	// in the same order.
	list(const list& right)
		: myData()
	{
		myData.myHead = new node;
		myData.myHead->myVal = Ty();
		myData.myHead->prev = myData.myHead->next = myData.myHead;

		nodePtr i = right.myData.myHead->next;
		for (; i != right.end(); i = i->next) {
			insert(end(), i->myVal);
		}
	}

	// List destructor
	// Destroys the container object.
	// Deallocates all the storage capacity allocated by the list container.
	~list()
	{
		clear();
		delete myData.myHead;
	}

	// Assigns new contents to the container, replacing its current contents,
	// and modifying its size accordingly.
	// Copies all the elements from "right" into the container
	// (with "right" preserving its contents).
	list& operator=(const list& right)
	{
		if (this != &right)
			if (size() < right.size()) {
				nodePtr i = begin();
				nodePtr j = right.myData.myHead->next;

				for (; i != end(); i = i->next, j = j->next) {
					i->myVal = j->myVal;
				}

				for (; j != right.end(); j = j->next) {
					insert(end(), j->myVal);
				}
			}
			else { //size() >= right.size()
				nodePtr i = begin();
				nodePtr j = right.myData.myHead->next;

				for (; j != right.end(); i = i->next, j = j->next) {
					i->myVal = j->myVal;
				}

				if (size() > right.size()) {
					for (; i != end(); i = i->next) {
						erase(i);
					}
				}
			}

		return *this;
	}

	// Returns an iterator pointing to the first element in the list container.
	// If the container is empty, the returned iterator value shall not be dereferenced.
	iterator begin()
	{
		return iterator(myData.myHead->next);
	}

	// Returns an iterator pointing to the first element in the list container.
	// If the container is empty, the returned iterator value shall not be dereferenced.
	const_iterator begin() const
	{
		return const_iterator(myData.myHead->next);
	}

	// Returns an iterator referring to the past-the-end element in the list container.
	// The past-the-end element is the theoretical element
	// that would follow the last element in the list container.
	// It does not point to any element, and thus shall not be dereferenced.
	// If the container is empty, this function returns the same as list::begin.
	iterator end()
	{
		return iterator(myData.myHead);
	}

	// Returns an iterator referring to the past-the-end element in the list container.
	// The past-the-end element is the theoretical element
	// that would follow the last element in the list container.
	// It does not point to any element, and thus shall not be dereferenced.
	// If the container is empty, this function returns the same as list::begin.
	const_iterator end() const
	{
		return const_iterator(myData.myHead);
	}

	// Returns the number of elements in the list container.
	size_type size() const
	{
		return myData.mySize;
	}

	// Returns whether the list container is empty (i.e. whether its size is 0).
	bool empty() const
	{
		return myData.mySize == 0;
	}

	// Returns a reference to the first element in the list container.
	// Calling this function on an empty container causes undefined behavior.
	reference front()
	{
		return myData.myHead->next->myVal;
	}

	// Returns a reference to the first element in the list container.
	// Calling this function on an empty container causes undefined behavior.
	const_reference front() const
	{
		return myData.myHead->next->myVal;
	}

	// Returns a reference to the last element in the list container.
	// Calling this function on an empty container causes undefined behavior.
	reference back()
	{
		return myData.myHead->prev->myVal;
	}

	// Returns a reference to the last element in the list container.
	// Calling this function on an empty container causes undefined behavior.
	const_reference back() const
	{
		return myData.myHead->prev->myVal;
	}

	// The container is extended by inserting a new element
	// before the element at the specified position.
	// This effectively increases the list size by the amount of elements inserted.
	// Returns an iterator that points to the newly inserted element.
	iterator insert(const_iterator where, const Ty& val) // insert val at where
	{
		nodePtr newNode = new node;
		newNode->myVal = val;

		nodePtr old_position = begin();
		for (; old_position != where; old_position = old_position->next);

		newNode->next = old_position;
		newNode->prev = old_position->prev;
		old_position->prev->next = newNode;
		old_position->prev = newNode;

		myData.mySize++;
		return iterator(newNode);
	}

	// Removes from the list container the element at the specified position.
	// This effectively reduces the container size one, which is destroyed.
	// Returns an iterator pointing to the element that followed the element erased.
	// This is the container end if the operation erased the last element in the sequence.
	iterator erase(const_iterator where)
	{
		if (myData.mySize == 0)
			return myData.myHead;

		nodePtr old_position = begin();
		for (; old_position != where; old_position = old_position->next);

		old_position->next->prev = old_position->prev;
		old_position->prev->next = old_position->next;

		myData.mySize--;
		return iterator(old_position);
	}

	// Removes all elements from the list container (which are destroyed),
	// and leaving the container with a size of 0.
	void clear() // erase all
	{
		if (myData.mySize != 0) // the list is not empty
		{
			nodePtr ptr = myData.myHead;
			myData.myHead = new node;
			myData.myHead->myVal = Ty();
			myData.myHead->prev = myData.myHead->next = myData.myHead;
			delete ptr;
		}
	}

private:
	ScaryVal myData;
};

// determine if two lists are equal and return true, otherwise return false
template< typename Ty >
bool operator==(const list< Ty >& left, const list< Ty >& right)
{
	if (left.size() != right.size())
		return false;
	else {
		typename list< Ty >::const_iterator it1 = left.begin();
		typename list< Ty >::const_iterator it2 = right.begin();
		for (; it1 != left.end(); it1 = it1->next, it2 = it2->next){
			if (it1->myVal != it2->myVal)
				return false;
		}
		return true;
	}
}

template< typename Ty >
bool operator!=(const list< Ty >& left, const list< Ty >& right)
{
	return !(left == right);
}

#endif // LIST