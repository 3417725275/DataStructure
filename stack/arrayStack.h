#pragma once

#ifndef _arrayStack_H_
#define _arrayStack_H_

#include "../arrayList/changeLength1D.h"


template<typename T>
class arrayStack
{
public:
	arrayStack(int initialCapacity = 10);
	~arrayStack() { delete[] stack; }
	bool empty() const { return stackTop == -1; }
	int size() const { return stackTop + 1; }
	T& top()
	{
		if (stackTop == -1)
			return;
		return stack[stackTop];
	}

	void pop()
	{
		if (stackTop == -1)
			return;
		stack[stackTop--].~T();  //����
	}
	void push(const T& theElement);

private:
	int stackTop;//ջ��Ԫ������
	int arrayLength;//ջ����
	T *stack;//���飬���ջԪ��
};

template<typename T>
 arrayStack<T>::arrayStack(int initialCapacity)
{
	//���ݼ��
	if (initialCapacity < 1)
	{
		std::cout << "Initial Capacity=" << initialCapacity << "Must be > 0";
	}
	arrayLength = initialCapacity;
	stack = new T[arrayLength];
	stackTop = -1;

}

template<typename T>
 void arrayStack<T>::push(const T & theElement)
{
	//���ݼ��
	if (stackTop == arrayLength - 1)
	{
		changeLength1D(stack, arrayLength, 2.0*arrayLength);
		arrayLength *= 2;
	}
	// ��ջ�����Ԫ��
	stack[++stackTop] = theElement;
}


#endif