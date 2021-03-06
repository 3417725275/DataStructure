#pragma once
//数组描述的线性表
//从线性表的抽象类linearList中继承
//对所有的方法都进行重写
//通过STL模板算法可以简化代码

#ifndef _arrayList_H_
#define _arrayList_H_
#include <iostream>
#include <algorithm>

#include "changeLength1D.h"


template <typename T>
class arraylist
{
public:
	//构造、拷贝、析构
	arraylist(int initialCapacity);
	arraylist(const arraylist<T> &);
	~arraylist() { delete[] element; }

	//继承过来的抽象方法
	bool empty()const { return listSize == 0; }//仅当线性表为空时返回true
	int size()const { return listSize; }//返回线性表元素的个数
	T& get(int theIndex) const;//返回索引为theIndex的元素
	int indexOf(const T& theElement);//求元素theElement第一次出现时的索引
	void erase(int theIndex);//删除索引为theIndex的元素
	void insert(int theIndex, const T& theElement) = 0;//把theElement元素插入到索引theIndex处
	void output(ostream & out)const = 0;//输出线性表


protected:
	void checkIndex(int theIndex) const;//检查索引值是否正确
	T*element; //存储线性表元素的一维数组
	int arrayLength; //一维数组的容量
	int listSize;//线性表的元素个数

};

template <typename T>
void arraylist<T>::checkIndex(int theIndex) const
{
	if (theIndex<0 || theIndex>listSize)
	{//无效索引
		ostringstream s;
		s << "index=" << theIndex << "must be>=0 and <=" << listSize;
		return;
	}
}

template <typename T>
arraylist<T>::arraylist(int initialCapacity = 10)
{
	//数据检查
	if (initialCapacity < 1)
	{
		std::cout << "Initial capacity=" << initialCapacity << "must be >0";
		return;
	}
	arrayLength = initialCapacity;
	element = new T[arrayLength];
	listSize = 0;
}

template <typename T>
arraylist<T>::arraylist(const arraylist<T> &thelist)
{
	//数据检查

	arrayLength = thelist.arrayLength;
	listSize = thelist.listSize;
	element = new T[arrayLength];//动态数组的拷贝
								 //如果element=thelist.element,会造成内存泄露，因为this.element还没有释放
	copy(thelist.element, thelist.element + listSize, element);

}


template <typename T>
void arraylist<T>::output(ostream & out) const
{
	//数据检查
	copy(element, element + listSize, ostream_iterator<T>(cout, " "));
}


template <typename T>
void arraylist<T>::insert(int theIndex, const T& theElement)
{
	//数据检查
	if (theIndex<0 || theIndex>listSize)
	{//无效索引
		std::cout << "index=" << theIndex << "must be>=0 and <=" << listSize;
		return;
	}
	if (listSize == arrayLength)
	{//数组已满，加倍
		changeLength1D(element, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}
	copy_backward(element + theIndex, element + listSize, element + listSize + 1);
	//copy_backward函数是从最后一个元素向前复制
	element[theIndex] = theElement;
	listSize++;
}

template <typename T>
void arraylist<T>::erase(int theIndex)
{
	//数据检查
	checkIndex(theIndex);
	copy(element + theIndex + 1, element + listSize, element + theIndex);

	element[--listSize].~T();
}

template <typename T>
int arraylist<T>::indexOf(const T& theElement)
{//返回第一次出现元素theElement的索引
	int theIndex = STATIC_CAST<int>(find(element, element + listSize, theElement) - element);

	//确定元素theElement是否找到
	if (theIndex == listSize)
		return -1;
	else
		return theIndex;
}

template <typename T>
T& arraylist<T>::get(int theIndex) const
{//返回索引为theIndex的元素

	checkIndex(theIndex);
	return element[theIndex];

}

template <typename T>
ostream& operator<<(ostream& out, const arraylist<T>& x)
{
	//数据检查
	x.output(out);
	return out;
}

#endif



