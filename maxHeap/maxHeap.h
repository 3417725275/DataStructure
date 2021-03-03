#pragma once
//大根堆，优先级队列的一种(最大优先级队列)

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
	//插入操作
	void push(const T&);
	//初始化一个非空大根堆,也叫堆排序
	void initialize(T *, int);
	void deactivateArray() { heap = NULL; arraylength = heapsize = 0; }


private:
	int heapsize;//队列中元素数量
	int arraylength; //堆的容量
	T* heap;//堆数组
};

template<typename T>
void maxHeap<T>::pop()
{
	//具体流程见P301

	if (heapsize == 0)
		return;

	heap[1].~T();

	// 为什么要取出最后一个元素，因为删除掉了一个元素，就要从最后取出一个元素插入到前面
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
		heap[currentNode] = heap[child]; //将根节点左右孩子中较大的作为新的根
		currentNode = child;             // move down a level
		child *= 2;
	}
	heap[currentNode] = lastElement;

}

template<typename T>
void maxHeap<T>::push(const T & theElement)//时间复杂度O(height)=O(logn)
{
	
	if (heapsize == arraylength - 1)//堆已满
	{
		changeLength1D(heap, arraylength, 2 * arraylength);
		arraylength *= 2;
	}

	//先插入一个新的节点，然后通过起泡操作调整其位置
	int currentNode = ++heapsize;
	while (currentNode != 1 && heap[currentNode / 2] < theElement) //currentNode/2是其父节点编号
	{
		//我不是根节点，且我比我的父节点还大
		heap[currentNode] = heap[currentNode / 2]; //把父节点的值放到我的位置来，我的位置本来为空
		currentNode /= 2; //我移动到我父节点的位置，然后再次和父节点比较
	}
	heap[currentNode] = theElement; //我的值没有父节点大了，或者我已经是根节点了，那么存储我的值
}

template<typename T>
void maxHeap<T>::initialize(T *theHeap, int theSize)
{
	//初始化大根堆数组，初始化从theHeap[1:theSize];0位置不存放元素
	delete[] heap;
	heap = theHeap;  //拷贝新的树过来，需要重新排序
	heapsize = theSize;

	//heapify 
	//heapsize/2为最后一个叶子节点的根节点，如果heapsize=1，那么就不对了，
	for (int root = heapsize / 2; root >= 1; root--)
	{
		T rootElement = heap[root]; //rootElement是要调整的值

		//查找插入rootElement元素的位置
		int child = 2 * root; // 找到这个根节点的左孩子节点
		while (child < heapsize)  //左孩子节点存在，child>heapsize表示该节点是叶节点
		{
			if (child < heapsize && heap[child] < heap[child + 1])
				child++;  //如果左孩子节点存在并且左孩子节点小于右孩子节点，那么child变成右孩子节点位置
						  //总之child就是找到左右孩子节点中大的那个

			if (rootElement >= heap[child])  //根元素是否比孩子节点大
				break;  // 根元素比孩子节点大，那么跳出循环

						// 根元素比孩子节点小
			heap[child / 2] = heap[child]; // 把孩子节点移上去，根节点的值之前保存在rootElement中了
			child *= 2;                    // 移到下一层
		}
		heap[child / 2] = rootElement;

	}
}

#endif