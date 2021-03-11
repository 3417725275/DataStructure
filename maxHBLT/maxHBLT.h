#pragma once

//��������

#ifndef _maxHBLT_H_
#define _maxHBLT_H_

#include "BinaryTree.h"
#include <queue>

template<typename T>
class maxHblt : public BinaryTree<T>
{
public:
	maxHblt():root(nullptr) {}
	~maxHblt() { delete root; }

	bool empty() const { return BinaryTree<T>::empty(); }
	int size() const { return BinaryTree<T>::size(); }

	//��������Ԫ��
	const T& top()
	{
		if (this->size() != 0)
			return root->GetData();
	}
	//ɾ�����Ԫ��
	void pop();
	//���Ԫ��
	void push(const T&);
	//���HBLT�ĳ�ʼ��
	BinaryTreeNode<T>* initialize(const T*, const int &);

	//�ϲ�theHblt����Hblt
	void meld(maxHblt<T>& theHblt) { meld(root, theHblt.root); }


private:
	//ʵ�ֹ��̼�P308 12.5.4
	void meld(BinaryTreeNode<T>* &, BinaryTreeNode<T>* &);//�������HBLT�ϲ�
	BinaryTreeNode<T>* root;
};


template<typename T>
void maxHblt<T>::pop()
{
	if (root == nullptr)
		return;
	BinaryTreeNode<T> *left = root->Getleftchild();
	BinaryTreeNode<T> *right = root->Getrightchild();
	delete root;
	root = left;
	meld(right);
}

template<typename T>
void maxHblt<T>::push(const T & theElement)
{
	BinaryTreeNode<T>*q = new BinaryTreeNode<T>(theElement);
	meld(q);
}

template<typename T>
BinaryTreeNode<T>* maxHblt<T>::initialize(const T * theElements, const int &theSize)
{
	if (theSize <= 0)
		return nullptr;

	maxHblt<T>* newtree = new BinaryTreeNode<T>(theElements[0]);
	queue<BinaryTreeNode<T>*> q(theSize);
	for (int i = 0; i < theSize; i++)
		q.push(new BinaryTreeNode<T>(theElements[i]));

	for (int i=0;i<theSize-1;i++)
	{
		BinaryTreeNode<T>* lftree = q.front();
		q.pop();
		BinaryTreeNode<T>* rhtree = q.front();
		q.pop();
		meld(lftree, rhtree);
		newtree = lftree;
		q.push(newtree);
	}
	return newtree;
}

template<typename T>
void maxHblt<T>::meld(BinaryTreeNode<T> *&x, BinaryTreeNode<T> *&y)
{
	// �������HBLT�ĺϲ� ��*x ��*y,�ϲ������Ϊx
	if (y == NULL)
		return;
	if (x == NULL)
	{
		x = y;
		return;
	}
	//�ȱȽϸ�Ԫ�أ��ϴ�����Ϊ�ϲ���ĸ�
	if (x->GetData() < y->GetData())
	{
		//����λ�ã����ϴ�ķ������
		BinaryTreeNode<T>* temp = x;
		x = y;
		y = temp;
	}

	meld(x->Getrightchild(), y);//x������������������y�ϲ�

	if (x->Getleftchild() == nullptr) //���������Ϊ�գ���Ҫ������������
	{
		x->Setleftchild(x->Getrightchild());
		x->Setrightchild(nullptr);
		x->Set_s(1);//��s��ֵ����Ϊ1
	}
	else//������������Ϊ�գ��Ƚ�����������Ԫ�ص�sֵ�Ĵ�С�������Ƿ�Ҫ����
	{
		BinaryTreeNode<T>* lc = x->Getleftchild();
		BinaryTreeNode<T>* rc = x->Getrightchild();
		if (lc->Get_s() < rc->Get_s())
		{
			x->Setleftchild(rc);
			x->Setrightchild(lc);
		}
		x->Set_s(x->Getrightchild()->Get_s() + 1)
	}
}


#endif