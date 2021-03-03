#pragma once
//����ѣ����ȼ����е�һ��(������ȼ�����)

#ifndef _maxHeap_H_
#define _maxHeap_H_

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
	void push(const T&);
	void initialize(T *, int);
	void deactivateArray() { heap = NULL; arraylength = heapsize = 0; }
	void output(ostream& out)const;

private:
	int heapsize;//������Ԫ������
	int arraylength; //queue capacity + 1
	T* heap;//������
};

template<typename T>
void maxHeap<T>::pop()
{
	if (heapsize == 0)
		return;

	heap[1].~T();

	// Remove last element and reheapify
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
		heap[currentNode] = heap[child]; //���ҽڵ���Ϊ���ڵ�
		currentNode = child;             // move down a level
		child *= 2;
	}

	heap[currentNode] = lastElement;
}
#endif