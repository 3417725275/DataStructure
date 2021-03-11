#pragma once

//最大左高树

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

	//返回最大的元素
	const T& top()
	{
		if (this->size() != 0)
			return root->GetData();
	}
	//删除最大元素
	void pop();
	//添加元素
	void push(const T&);
	//最大HBLT的初始化
	BinaryTreeNode<T>* initialize(const T*, const int &);

	//合并theHblt到本Hblt
	void meld(maxHblt<T>& theHblt) { meld(root, theHblt.root); }


private:
	//实现过程见P308 12.5.4
	void meld(BinaryTreeNode<T>* &, BinaryTreeNode<T>* &);//两颗最大HBLT合并
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
	// 两颗最大HBLT的合并 根*x 和*y,合并后的树为x
	if (y == NULL)
		return;
	if (x == NULL)
	{
		x = y;
		return;
	}
	//先比较根元素，较大者作为合并后的根
	if (x->GetData() < y->GetData())
	{
		//交换位置，根较大的放在左边
		BinaryTreeNode<T>* temp = x;
		x = y;
		y = temp;
	}

	meld(x->Getrightchild(), y);//x作根，它的右子树和y合并

	if (x->Getleftchild() == nullptr) //左子树如果为空，需要交换左右子树
	{
		x->Setleftchild(x->Getrightchild());
		x->Setrightchild(nullptr);
		x->Set_s(1);//把s的值设置为1
	}
	else//左右子树均不为空，比较左右子树根元素的s值的大小，决定是否要交换
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