#pragma once

// 容器描述的线性表

#ifndef _vectorList_H_
#define _vectorList_H_

#include<iostream>

#include<string>
#include<vector>
#include<algorithm>
#include<iterator>


using namespace std;

template<class T>
class vectorlist 
{
public:
	// constructor, copy constructor and destructor
	vectorlist(int initialCapacity = 10);
	vectorlist(const vectorlist<T>&);
	~vectorlist() { delete element; }


	bool empty() const { return element->empty(); }
	int size() const { return (int)element->size(); }
	T& get(int theIndex) const;
	int indexOf(const T& theElement) const;
	void erase(int theIndex);
	void insert(int theIndex, const T& theElement);
	void output(ostream& out) const;

	// additional method
	int capacity() const { return (int)element->capacity(); }

	// iterators to start and end of list
	typedef typename vector<T>::iterator iterator;
	iterator begin() { return element->begin(); }
	iterator end() { return element->end(); }

protected:  // additional members of vectorlist
	void checkIndex(int theIndex) const;
	vector<T>* element;     // vector to hold list elements
};

template<class T>
vectorlist<T>::vectorlist(int initialCapacity)
{// Constructor.
	if (initialCapacity < 1)
	{
		std::cout << "Initial capacity = " << initialCapacity << " Must be > 0";
		return;
	}

	element = new vector<T>; // create an empty vector with capacity 0
	element->reserve(initialCapacity);	// increase vector capacity from 0 to initialCapacity
}

template<class T>
vectorlist<T>::vectorlist(const vectorlist<T>& theList)
{// Copy constructor.
	element = new vector<T>(*theList.element);//相当于对vector进行拷贝初始化
											  //相当于element =new vector<T>,然后对element进行初始化
}

template<class T>
void vectorlist<T>::checkIndex(int theIndex) const
{// Verify that theIndex is between 0 and size() - 1.
	if (theIndex < 0 || theIndex >= size())
	{
		std::cout<< "index = " << theIndex << " size = " << size();
		return;
	}

}

template<class T>
T& vectorlist<T>::get(int theIndex) const
{// Return element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
	checkIndex(theIndex);
	return (*element)[theIndex];
}

template<class T>
int vectorlist<T>::indexOf(const T& theElement) const
{// Return index of first occurrence of theElement.
 // Return -1 if theElement not in list.

 // search for theElement
	int theIndex = (int)(find(element->begin(), element->end(),theElement)-element->begin());

	// check if theElement was found
	if (theIndex == size()) // not found
		return -1;
	else return theIndex;
}

template<class T>
void vectorlist<T>::erase(int theIndex)
{// Delete the element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
	checkIndex(theIndex);
	element->erase(begin() + theIndex);
}

template<class T>
void vectorlist<T>::insert(int theIndex, const T& theElement)
{// Insert theElement so that its index is theIndex.
	if (theIndex < 0 || theIndex > size())
	{// invalid index
		ostringstream s;
		std::cout << "index = " << theIndex << " size = " << size();
	}

	element->insert(element->begin() + theIndex, theElement);
	// may throw an uncaught exception if insufficient
	// memory to resize vector
}

template<class T>
void vectorlist<T>::output(ostream& out) const
{// Put the list into the stream out.
	copy(element->begin(), element->end(), ostream_iterator<T>(cout, "  "));
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const vectorlist<T>& x)
{
	x.output(out); return out;
}

#endif
