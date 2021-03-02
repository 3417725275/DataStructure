#pragma once
//二叉搜索树，也称二叉排序树
//树节点除了有指向左右孩子节点的指针，还有一个键值成员，用来排序

//相当于在原有的二叉树基础上加了排序，排序可以根据节点的值，也可以另外加一个键值
//这里直接用二叉树的节点值进行排序

#ifndef _BSTree_H
#define _BSTree_H
#include "BinaryTree.h"


template<typename T>
class BSTree :public BinaryTree<T>
{
public:
	//构造函数
	BSTree() :BinaryTree() {}
	BSTree(BinaryTreeNode<T>* x) :BinaryTree(x) {}

	//子类隐藏父类同名函数
	//bool empty() const { return BinaryTree::empty(); }
	//int size() const { return BinaryTree::size(); }
	//BinaryTreeNode<T>* find(const T& item) const { return BinaryTree::find(item); }
	//bool insert(const T& item) { return BinaryTree::insert(item); }

	void erase(const T& item);
};


template<typename T>
void BSTree<T>::erase(const T & item)
{
	//查找关键字为item的节点
	BinaryTreeNode<T>*dnode = find(item);
	if (dnode == nullptr)
		return;

	//dnode有两个孩子时
	BinaryTreeNode<T>* pleft = dnode->Getleftchild();
	BinaryTreeNode<T>* pright = dnode->Getrightchild();
	if (pleft != nullptr && pright != nullptr)
	{
		//在dnode的左子树中寻找最大的元素(parent)    ，也可将右子树的最小元素移到dnode
		BinaryTreeNode<T> *max = dnode, *s = pleft;
		while (s != nullptr)
		{
			max = s;
			s = s->Getrightchild();
		}

		//将左子树最大元素max移到dnode
		BinaryTreeNode<T>* q = new BinaryTreeNode<T>(max->GetData(), pleft, pright);

		



		delete dnode;
		dnode = nullptr;
	}
}

#endif