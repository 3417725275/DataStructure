#pragma once
//大根堆，优先级队列的一种(最大优先级队列)

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

	//返回最大的值
	const T& top()
	{	
		if (heapsize != 0)
			return heap[1];
		//因为大根堆从大到小排列，所以第一个元素肯定是最大的值
		return;
	}

	//删除操作：每次删除最大的元素
	void pop();
	void push(const T&);
	void initialize(T *, int);
	void deactivateArray() { heap = NULL; arraylength = heapsize = 0; }
	void output(ostream& out)const;

private:
	int heapsize;//队列中元素数量
	int arraylength; //queue capacity + 1
	T* heap;//堆数组
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
	int currentNode = 1, child = 2;//child相当于编号

	while (child <= heapsize)
	{
		// heap[child] should be larger child of currentNode
		if (child < heapsize && heap[child] < heap[child + 1])
			child++; //当左节点<右节点时，child为右节点

					 // can we put lastElement in heap[currentNode]?
		if (lastElement >= heap[child]) //如果最后一个值比右节点还大，那么作为根节点
			break;   // yes

					 // no
		heap[currentNode] = heap[child]; //将右节点作为根节点
		currentNode = child;             // move down a level
		child *= 2;
	}

	heap[currentNode] = lastElement;
}
#endif