#pragma once

#ifndef _BinaryTree_H
#define _BianryTree_H

#include "BinaryTreeNode.h"

template<typename T>
class BinaryTree
{
public:
	//构造
	BinaryTree() :root(nullptr) {}
	BinaryTree(BinaryTreeNode<T>* x) :root(x) {}

	//拷贝构造
	BinaryTree(BinaryTree<T> & x);

	//析构
	virtual ~BinaryTree() { root->Destory(); }
	//
	bool empty() const;
	int size() const;
	int height() const;

	//获取根、左右孩子或某节点的双亲节点
	BinaryTreeNode<T>* getRoot();
	BinaryTreeNode<T>* getleftchild();
	BinaryTreeNode<T>* getleftchild(BinaryTreeNode<T>* &node);
	BinaryTreeNode<T>* getrightchild();
	BinaryTreeNode<T>* getrightchild(BinaryTreeNode<T>* &node);
	BinaryTreeNode<T>* getParent(BinaryTreeNode<T>* &node);//获取某一结点的双亲结点

	//前中后序遍历
	void PreOrder() const;
	void InOrder() const;
	void PostOrder() const;
	void levelOrder() const;

	//查找和插入
	BinaryTreeNode<T>* find(T& dt) const;
	bool insert(const T& item);

private:
	BinaryTreeNode<T>* root;
	//在以rt为根的子树中寻找node的双亲节点
	BinaryTreeNode<T>* getParent(BinaryTreeNode<T>*& rt, BinaryTreeNode<T>*& node);
};

template<typename T>
BinaryTree<T>::BinaryTree(BinaryTree<T>& x)
{
	if (x.root != nullptr)
	{
		this->root = x.root;
	}
}

template<typename T>
bool BinaryTree<T>::empty() const
{
	if (root != nullptr)
		return false;
	return true;
}

template<typename T>
int BinaryTree<T>::size() const
{
	if (root != nullptr)
		return root->size();
	return 0;
}

template<typename T>
int BinaryTree<T>::height() const
{
	if (root != nullptr)
		return root->height();
	return 0;
}

template<typename T>
BinaryTreeNode<T>* BinaryTree<T>::getRoot()
{
	if (root != nullptr)
		return root;
	return nullptr;
}

template<typename T>
BinaryTreeNode<T>* BinaryTree<T>::getleftchild()
{
	return getleftchild(root);
}

template<typename T>
BinaryTreeNode<T>* BinaryTree<T>::getleftchild(BinaryTreeNode<T>*& node)
{
	if (node != nullptr)
		return node->leftchild();
	return nullptr;
}

template<typename T>
BinaryTreeNode<T>* BinaryTree<T>::getrightchild()
{
	return getrightchild(root);
}

template<typename T>
BinaryTreeNode<T>* BinaryTree<T>::getrightchild(BinaryTreeNode<T>*& node)
{
	if (node != nullptr)
		return node->Getrightchild();
	return nullptr;
}

template<typename T>
BinaryTreeNode<T>* BinaryTree<T>::getParent(BinaryTreeNode<T>*& node)
{
	if (this == nullptr || node == nullptr || node == this)
		return nullptr;
	return(this, node);
}

template<typename T>
void BinaryTree<T>::PreOrder() const
{
	if (this->root == nullptr)
		return;
	this->root->PreOrder();
}

template<typename T>
void BinaryTree<T>::InOrder() const
{
	if (this->root == nullptr)
		return;
	this->root->InOrder();
}

template<typename T>
void BinaryTree<T>::PostOrder() const
{
	if (this->root == nullptr)
		return;
	this->root->PostOrder();
}

template<typename T>
inline void BinaryTree<T>::levelOrder() const
{
	if (this->root == nullptr)
		return;
	this->root->levelOrder();

}

template<typename T>
 BinaryTreeNode<T>* BinaryTree<T>::find(T & dt) const
{
	return NULL;
}

template<typename T>
bool BinaryTree<T>::insert(const T & item)
{
	return false;
}

template<typename T>
BinaryTreeNode<T>* BinaryTree<T>::getParent(BinaryTreeNode<T>*& rt, BinaryTreeNode<T>*& node)
{
	if (rt == nullptr || node == nullptr)
		return nullptr;
	if (rt->leftchild == node || rt->rightchild == node)
		return rt;
	if (BinaryTreeNode<T>* temp = getParent(rt->leftchild, node))
		return temp;
	else
		return getParent(rt->rightchild, node);
}

#endif

