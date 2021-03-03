#pragma once
//二叉搜索树，也称二叉排序树
//树节点除了有指向左右孩子节点的指针，还有一个键值成员，用来排序

//相当于在原有的二叉树基础上加了排序，排序可以根据节点的值，也可以另外加一个键值
//这里直接用二叉树的节点值进行排序

#ifndef _BSTree_H_
#define _BSTree_H_
#include "BinaryTree.h"


template<typename T>
class BSTree :public BinaryTree<T>
{
public:
	//构造函数
	BSTree() :BinaryTree() {}
	BSTree(BinaryTreeNode<T>* x);

	//子类隐藏父类同名函数
	//bool empty() const { return BinaryTree::empty(); }
	//int size() const { return BinaryTree::size(); }
	//BinaryTreeNode<T>* find(const T& item) const { return BinaryTree::find(item); }
	//bool insert(const T& item) { return BinaryTree::insert(item); }

	void erase(const T& item);
	BinaryTreeNode<T>* makeBSTree(T* element, int n);
};

template<typename T>
BSTree<T>::BSTree(BinaryTreeNode<T>* x)
{
	while (x != nullptr)
	{
		insert(x->data);
		if ((x = x->Getleftchild()) == nullptr)
		{
			x = x->Getrightchild();
		}
	}
}

template<typename T>
void BSTree<T>::erase(const T & item)
{
	//查找关键字为item的节点
	BinaryTreeNode<T>*dNode = find(item);
	if (dNode == nullptr)
		return;
	BinaryTreeNode<T>* pdNode = getParent(dNode);

	//dNode有两个孩子时
	BinaryTreeNode<T>* pleft = dNode->Getleftchild();
	BinaryTreeNode<T>* pright = dNode->Getrightchild();
	if (pleft != nullptr && pright != nullptr)
	{
		//在dNode的左子树中寻找最大的元素(parent)    ，也可将右子树的最小元素移到dNode
		BinaryTreeNode<T> *parent = dNode, *max = pleft, *temp;
		while (temp = max->Getrightchild() != nullptr)
		{
			parent = max;  //左子树最大元素的双亲
			max = temp;  //左子树最大元素
		}

		//将左子树最大元素max移到dNode
		BinaryTreeNode<T>* q = new BinaryTreeNode<T>(max->GetData(), pleft, pright);
		if (pdNode == nullptr) //要删除的节点是树的根节点
			root = q;
		else if (dNode == pdNode->Getleftchild()) //要删除的是某个根的左孩子节点
			pdNode->Setleftchild(dNode);
		else                         //要删除的是某个根的右孩子节点
			pdNode->Setrightchild(dNode);

		//这块需要完善，特殊情况！如果左子树最大元素是要删除节点的孩子节点,P344图14-4(a)的情况
		if (parent == dNode)//
		{
			q->Setleftchild(max->Getleftchild());
			delete max;
		}
		else
		{
			parent->Setrightchild(nullptr);
			delete max;
		}
		delete dNode;
		dNode = nullptr;
	}


	//dNode最多只有一个孩子,child存放其孩子
	BinaryTreeNode<T>* child = pdNode->Getleftchild();
	if (child == nullptr)
		child = pdNode->Getrightchild();
	if (child == nullptr)//两颗子树均为空
	{
		delete pdNode;
		return;
	}

	if (dNode == root)
		root = child;
	else //dNode是左孩子还是右孩子
	{
		if (dNode = pdNode->Getleftchild())
			pdNode->Setleftchild(child);
		else
			pdNode->Setrightchild(child);
	}
	delete pdNode;

}

template<typename T>
BinaryTreeNode<T>* BSTree<T>::makeBSTree(T* element, int n)
{
	BinaryTreeNode<T>* rootTree = root;
	root = nullptr;
	for (int i=0;i<n;i++)
	{
		insert(element[i]);
	}
	BinaryTreeNode<T>* bstree = root;
	root = rootTree;
	return bstree;
}

#endif