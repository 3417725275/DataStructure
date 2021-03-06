#pragma once
//�������������Ա�
//�����Ա�ĳ�����linearList�м̳�
//�����еķ�����������д
//ͨ��STLģ���㷨���Լ򻯴���

#ifndef _arrayList_H_
#define _arrayList_H_
#include <iostream>
#include <algorithm>

#include "changeLength1D.h"


template <typename T>
class arraylist
{
public:
	//���졢����������
	arraylist(int initialCapacity);
	arraylist(const arraylist<T> &);
	~arraylist() { delete[] element; }

	//�̳й����ĳ��󷽷�
	bool empty()const { return listSize == 0; }//�������Ա�Ϊ��ʱ����true
	int size()const { return listSize; }//�������Ա�Ԫ�صĸ���
	T& get(int theIndex) const;//��������ΪtheIndex��Ԫ��
	int indexOf(const T& theElement);//��Ԫ��theElement��һ�γ���ʱ������
	void erase(int theIndex);//ɾ������ΪtheIndex��Ԫ��
	void insert(int theIndex, const T& theElement) = 0;//��theElementԪ�ز��뵽����theIndex��
	void output(ostream & out)const = 0;//������Ա�


protected:
	void checkIndex(int theIndex) const;//�������ֵ�Ƿ���ȷ
	T*element; //�洢���Ա�Ԫ�ص�һά����
	int arrayLength; //һά���������
	int listSize;//���Ա��Ԫ�ظ���

};

template <typename T>
void arraylist<T>::checkIndex(int theIndex) const
{
	if (theIndex<0 || theIndex>listSize)
	{//��Ч����
		ostringstream s;
		s << "index=" << theIndex << "must be>=0 and <=" << listSize;
		return;
	}
}

template <typename T>
arraylist<T>::arraylist(int initialCapacity = 10)
{
	//���ݼ��
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
	//���ݼ��

	arrayLength = thelist.arrayLength;
	listSize = thelist.listSize;
	element = new T[arrayLength];//��̬����Ŀ���
								 //���element=thelist.element,������ڴ�й¶����Ϊthis.element��û���ͷ�
	copy(thelist.element, thelist.element + listSize, element);

}


template <typename T>
void arraylist<T>::output(ostream & out) const
{
	//���ݼ��
	copy(element, element + listSize, ostream_iterator<T>(cout, " "));
}


template <typename T>
void arraylist<T>::insert(int theIndex, const T& theElement)
{
	//���ݼ��
	if (theIndex<0 || theIndex>listSize)
	{//��Ч����
		std::cout << "index=" << theIndex << "must be>=0 and <=" << listSize;
		return;
	}
	if (listSize == arrayLength)
	{//�����������ӱ�
		changeLength1D(element, arrayLength, 2 * arrayLength);
		arrayLength *= 2;
	}
	copy_backward(element + theIndex, element + listSize, element + listSize + 1);
	//copy_backward�����Ǵ����һ��Ԫ����ǰ����
	element[theIndex] = theElement;
	listSize++;
}

template <typename T>
void arraylist<T>::erase(int theIndex)
{
	//���ݼ��
	checkIndex(theIndex);
	copy(element + theIndex + 1, element + listSize, element + theIndex);

	element[--listSize].~T();
}

template <typename T>
int arraylist<T>::indexOf(const T& theElement)
{//���ص�һ�γ���Ԫ��theElement������
	int theIndex = STATIC_CAST<int>(find(element, element + listSize, theElement) - element);

	//ȷ��Ԫ��theElement�Ƿ��ҵ�
	if (theIndex == listSize)
		return -1;
	else
		return theIndex;
}

template <typename T>
T& arraylist<T>::get(int theIndex) const
{//��������ΪtheIndex��Ԫ��

	checkIndex(theIndex);
	return element[theIndex];

}

template <typename T>
ostream& operator<<(ostream& out, const arraylist<T>& x)
{
	//���ݼ��
	x.output(out);
	return out;
}

#endif



