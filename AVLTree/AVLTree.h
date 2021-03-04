#pragma once
//ƽ�������

#ifndef _AVLTree_H_
#define _AVLTree_H_
#include "BinaryTree.h"

template<typename T>
class AVLTree :public BinaryTree
{
	void insert(const T& elem);
	void erase(const T& elem);

	//LL������x����С��ƽ��������ĸ��ڵ�
	BinaryTreeNode<T>* LL_rotate(BinaryTreeNode<T>* x);
	//RR������x����С��ƽ��������ĸ��ڵ�
	BinaryTreeNode<T>* RR_rotate(BinaryTreeNode<T>* x);
	//LR˫����x����С��ƽ��������ĸ��ڵ�
	BinaryTreeNode<T>* LR_rotate(BinaryTreeNode<T>* x);
	//RL˫����x����С��ƽ��������ĸ��ڵ�
	BinaryTreeNode<T>* RL_rotate(BinaryTreeNode<T>* x);

private:
	//����xΪ����ƽ��������в���elem
	BinaryTreeNode<T>* insert(const T& elem, BinaryTreeNode<T>* x);
	//����xΪ����ƽ���������ɾ��elem
	BinaryTreeNode<T>* erase(const T& elem, BinaryTreeNode<T>* x);

};



template<typename T>
BinaryTreeNode<T>* AVLTree<T>::LL_rotate(BinaryTreeNode<T>* x)
{
	BinaryTreeNode<T>* newroot = x->Getleftchild();
	x->Setleftchild(newroot->Getrightchild());
	newroot->Setrightchild(x);
	return newroot;
}

template<typename T>
BinaryTreeNode<T>* AVLTree<T>::RR_rotate(BinaryTreeNode<T>* x)
{
	BinaryTreeNode<T>* newroot = x->Getrightchild();
	x->Setrightchild(newroot->Getleftchild());
	newroot->Setleftchild(x);
	return newroot;
}

template<typename T>
BinaryTreeNode<T>* AVLTree<T>::LR_rotate(BinaryTreeNode<T>* x)
{
	x->Setleftchild(RR_rotate(x->Getleftchild()));
	return LL_rotate(x);
}

template<typename T>
BinaryTreeNode<T>* AVLTree<T>::RL_rotate(BinaryTreeNode<T>* x)
{
	x->Setrightchild(LL_rotate(x->Getrightchild()));
	return RR_rotate(x);
}

template<typename T>
BinaryTreeNode<T>* AVLTree<T>::insert(const T & elem, BinaryTreeNode<T>* x)
{
	if (x == nullptr)
	{
		x = new BinaryTreeNode<T>(elem);
		return x;
	}
	if (elem == x->GetData())
		return x;
	if (elem < x->GetData())
	{
		x->Setleftchild(insert(elem, x->Getleftchild());
		//���ﲹ��һ���жϲ�����Ƿ���ƽ���������������ǣ�Ҫ����

	}
	else
	{
		x->Setrightchild(insert(elem, x->Getrightchild()));
		//���ﲹ��һ���жϲ�����Ƿ���ƽ���������������ǣ�Ҫ����
	}

	
			if (2 == depth(x->lchild) - depth(x->rchild)) {
				if (elem < x->lchild->element)
					x = single_rotate_with_left(x);
				else
					x = double_rotate_with_left(x);
			}
		}//else if
		else {	//elem > x->element
			x->rchild = insert(elem, x->rchild);
			if (2 == depth(x->rchild) - depth(x->lchild)) {
				if (elem > x->rchild->element)
					x = single_rotate_with_right(x);
				else
					x = double_rotate_with_right(x);
			}
		}//else
	}//else
	return x;
}

#endif