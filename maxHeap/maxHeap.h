#pragma once
//����ѣ����ȼ����е�һ��(������ȼ�����)

#ifndef _maxHeap_H_
#define _maxHeap_H_

#include "changeLength1D.h"

template <typename T>
class maxHeap 
{
public:
	//construct
	maxHeap(int initialCapacity = 20) :heapsize(initialCapacity) {}
	~maxHeap() { delete[] heap; }
	//
	bool empty() const { return heapsize == 0; }
	int size() const { return heapsize; }

	//��������ֵ
	const T& top()
	{	
		if (heapsize != 0)
			return heap[1];
		//��Ϊ����ѴӴ�С���У����Ե�һ��Ԫ�ؿ϶�������ֵ
		return;
	}

	//ɾ��������ÿ��ɾ������Ԫ��
	void pop();
	//�������
	void push(const T&);
	//��ʼ��һ���ǿմ����,Ҳ�ж�����
	void initialize(T *, int);
	void deactivateArray() { heap = NULL; arraylength = heapsize = 0; }


private:
	int heapsize;//������Ԫ������
	int arraylength; //�ѵ�����
	T* heap;//������
};

template<typename T>
void maxHeap<T>::pop()
{
	//�������̼�P301

	if (heapsize == 0)
		return;

	heap[1].~T();

	// ΪʲôҪȡ�����һ��Ԫ�أ���Ϊɾ������һ��Ԫ�أ���Ҫ�����ȡ��һ��Ԫ�ز��뵽ǰ��
	T lastElement = heap[heapsize--];

	// find place for lastElement starting at root
	int currentNode = 1, child = 2;//child�൱�ڱ��

	while (child <= heapsize)
	{
		// heap[child] should be larger child of currentNode
		if (child < heapsize && heap[child] < heap[child + 1])
			child++; //����ڵ�<�ҽڵ�ʱ��childΪ�ҽڵ�

					 // can we put lastElement in heap[currentNode]?
		if (lastElement >= heap[child]) //������һ��ֵ���ҽڵ㻹����ô��Ϊ���ڵ�
			break;   // yes

					 // no
		heap[currentNode] = heap[child]; //�����ڵ����Һ����нϴ����Ϊ�µĸ�
		currentNode = child;             // move down a level
		child *= 2;
	}
	heap[currentNode] = lastElement;

}

template<typename T>
void maxHeap<T>::push(const T & theElement)//ʱ�临�Ӷ�O(height)=O(logn)
{
	
	if (heapsize == arraylength - 1)//������
	{
		changeLength1D(heap, arraylength, 2 * arraylength);
		arraylength *= 2;
	}

	//�Ȳ���һ���µĽڵ㣬Ȼ��ͨ�����ݲ���������λ��
	int currentNode = ++heapsize;
	while (currentNode != 1 && heap[currentNode / 2] < theElement) //currentNode/2���丸�ڵ���
	{
		//�Ҳ��Ǹ��ڵ㣬���ұ��ҵĸ��ڵ㻹��
		heap[currentNode] = heap[currentNode / 2]; //�Ѹ��ڵ��ֵ�ŵ��ҵ�λ�������ҵ�λ�ñ���Ϊ��
		currentNode /= 2; //���ƶ����Ҹ��ڵ��λ�ã�Ȼ���ٴκ͸��ڵ�Ƚ�
	}
	heap[currentNode] = theElement; //�ҵ�ֵû�и��ڵ���ˣ��������Ѿ��Ǹ��ڵ��ˣ���ô�洢�ҵ�ֵ
}

template<typename T>
void maxHeap<T>::initialize(T *theHeap, int theSize)
{
	//��ʼ����������飬��ʼ����theHeap[1:theSize];0λ�ò����Ԫ��
	delete[] heap;
	heap = theHeap;  //�����µ�����������Ҫ��������
	heapsize = theSize;

	//heapify 
	//heapsize/2Ϊ���һ��Ҷ�ӽڵ�ĸ��ڵ㣬���heapsize=1����ô�Ͳ����ˣ�
	for (int root = heapsize / 2; root >= 1; root--)
	{
		T rootElement = heap[root]; //rootElement��Ҫ������ֵ

		//���Ҳ���rootElementԪ�ص�λ��
		int child = 2 * root; // �ҵ�������ڵ�����ӽڵ�
		while (child < heapsize)  //���ӽڵ���ڣ�child>heapsize��ʾ�ýڵ���Ҷ�ڵ�
		{
			if (child < heapsize && heap[child] < heap[child + 1])
				child++;  //������ӽڵ���ڲ������ӽڵ�С���Һ��ӽڵ㣬��ôchild����Һ��ӽڵ�λ��
						  //��֮child�����ҵ����Һ��ӽڵ��д���Ǹ�

			if (rootElement >= heap[child])  //��Ԫ���Ƿ�Ⱥ��ӽڵ��
				break;  // ��Ԫ�رȺ��ӽڵ����ô����ѭ��

						// ��Ԫ�رȺ��ӽڵ�С
			heap[child / 2] = heap[child]; // �Ѻ��ӽڵ�����ȥ�����ڵ��ֵ֮ǰ������rootElement����
			child *= 2;                    // �Ƶ���һ��
		}
		heap[child / 2] = rootElement;

	}
}

#endif