#pragma once


//ͨ�����Ա�ʵ���ֵ����ݽṹ
//�������������Ա�
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
	pairNode<K, E>* firstNode; //�����ͷ�ڵ�
	int dSize;//�ֵ���Ԫ������

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
	//����ָ��ƥ��Ԫ�ص�ָ��
	//���û���ҵ����򷵻�NULL
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
	//tp��������ƥ��Ľڵ��ǰһ���ڵ�

	while (p != NULL && p->element.first < theKey)
	{
		tp = p;
		p = p->next;
	}

	if (p != NULL && p->element.first == theKey)
	{
		if (tp == nullptr)
		{//ƥ�����ͷ�ڵ�
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
	//tp����Ҫ�����λ�õ�ǰһ���ڵ�

	//���Ҳ����λ��
	while (p != NULL && p->element.first < thePair.first)
	{
		tp = p;
		p = p->next;
	}
	if (p != nullptr && p->element.first == thePair.first)
	{//�����ֵ��ȣ�����ֵ���Ǿ�ֵ
		p->element.second = thePair.second;
		return;
	}

	pairNode<K, E>*newNode = new pairNode<K, E>(thePair, p);
	if (tp == nullptr)
	{
		firstNode = newNode;//������ͷ�ڵ�
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
