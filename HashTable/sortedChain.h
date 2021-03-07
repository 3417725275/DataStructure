#pragma once


//通过线性表实现字典数据结构
//链表描述的线性表
#include "pairNode.h"


template<typename K, typename E>
class sortedChain 
{
public:
	sortedChain() { firstNode = nullptr; dSize = 0; }
	~sortedChain();
	bool empty() const { return dSize == 0; };
	int size() const { return dSize; };
	pair<const K, E>* find(const K&) const;
	void erase(const K&);
	void insert(const pair<const K, E>&);
	void output(ostream& out) const;

private:
	pairNode<K, E>* firstNode; //链表的头节点
	int dSize;//字典中元素数量

};

template<typename K, typename E>
sortedChain<K, E>::~sortedChain()
{
	while (firstNode != nullptr)
	{
		pairNode<K, E>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}

template<typename K, typename E>
pair<const K, E>* sortedChain<K, E>::find(const K& theKey) const
{
	//返回指向匹配元素的指针
	//如果没查找到，则返回NULL
	pairNode<K, E>* currentNode = firstNode;
	while (currentNode != NULL && currentNode->element.first != theKey)
	{
		currentNode = currentNode->next;
	}
	if (currentNode != NULL && currentNode->element.first == theKey)
		return &currentNode->element;
	else
		return NULL;
}

template<typename K, typename E>
void sortedChain<K, E>::erase(const K& theKey)
{

	pairNode<K, E>*p = firstNode, *tp = NULL;
	//tp用来保存匹配的节点的前一个节点

	while (p != NULL && p->element.first < theKey)
	{
		tp = p;
		p = p->next;
	}

	if (p != NULL && p->element.first == theKey)
	{
		if (tp == nullptr)
		{//匹配的是头节点
			firstNode = p->next;
		}
		else
		{
			tp->next = p->next;
		}
		delete p;
		dSize--;
	}

}

template<typename K, typename E>
void sortedChain<K, E>::insert(const pair<const K, E>& thePair)
{
	pairNode<K, E>*p = firstNode, *tp = nullptr;
	//tp保存要插入的位置的前一个节点

	//查找插入的位置
	while (p != NULL && p->element.first < thePair.first)
	{
		tp = p;
		p = p->next;
	}
	if (p != nullptr && p->element.first == thePair.first)
	{//如果键值相等，用新值覆盖旧值
		p->element.second = thePair.second;
		return;
	}

	pairNode<K, E>*newNode = new pairNode<K, E>(thePair, p);
	if (tp == nullptr)
	{
		firstNode = newNode;//插入在头节点
	}
	else
	{
		tp->next = newNode;
	}
	dSize++;
	return;
}

template<typename K, typename E>
void sortedChain<K, E>::output(ostream & out) const
{
	for (pairNode<K, E>* currentNode = firstNode; currentNode != NULL; currentNode = currentNode->next)
	{
		out << currentNode->element.first << " " << currentNode->element.second << " " << endl;
	}
}
