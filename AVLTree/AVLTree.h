#pragma once
//平衡二叉树

#ifndef _AVLTree_H_
#define _AVLTree_H_
#include "BinaryTree.h"

template<typename T>
class AVLTree :public BinaryTree
{
	void insert(const T& elem);
	void erase(const T& elem);

	//LL单旋，x是最小不平衡二叉树的根节点
	BinaryTreeNode<T>* LL_rotate(BinaryTreeNode<T>* x);
	//RR单旋，x是最小不平衡二叉树的根节点
	BinaryTreeNode<T>* RR_rotate(BinaryTreeNode<T>* x);
	//LR双旋，x是最小不平衡二叉树的根节点
	BinaryTreeNode<T>* LR_rotate(BinaryTreeNode<T>* x);
	//RL双旋，x是最小不平衡二叉树的根节点
	BinaryTreeNode<T>* RL_rotate(BinaryTreeNode<T>* x);

private:
	//在以x为根的平衡二叉树中插入elem
	BinaryTreeNode<T>* insert(const T& elem, BinaryTreeNode<T>* x);
	//在以x为根的平衡二叉树中删除elem
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
		//这里补充一个判断插入后是否是平衡二叉树，如果不是，要调整

	}
	else
	{
		x->Setrightchild(insert(elem, x->Getrightchild()));
		//这里补充一个判断插入后是否是平衡二叉树，如果不是，要调整
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