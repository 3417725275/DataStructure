#pragma once


#ifndef _BinaryTreeNode_H
#define _BinaryTreeNode_H
#include <iostream>
#include <queue>

template <typename T>
class BinaryTreeNode
{
public:
	//构造
	BinaryTreeNode() :leftchild(nullptr), rightchild(nullptr) {}
	BinaryTreeNode(const T& dt, const BinaryTreeNode<T>* &lc, const BinaryTreeNode<T>* &rc) :data(dt), leftchild(lc), rightchild(rc) {}
	BinaryTreeNode(const T& dt) :BinaryTreeNode(dt, nullptr, nullptr) {}

	//拷贝构造
	BinaryTreeNode(const BinaryTreeNode<T> & x);

	//获取成员值
	T GetData() { return this != nullptr ? data : -1; }
	BinaryTreeNode<T>* Getleftchild() const { return this != nullptr ? leftchild : nullptr; }
	BinaryTreeNode<T>* Getrightchild() const { return this != nullptr ? rightchild : nullptr; }

	//设置成员值
	void SetData(const T& dt)
	{
		if (this != nullptr)
		{
			data = dt;
		}
	}
	void Setleftchild(const BinaryTreeNode<T>* &lc)
	{
		if (this != nullptr)
		{
			leftchild = lc;
		}
	}
	void Setrightchild(const BinaryTreeNode<T>* &rc)
	{
		if (this != nullptr)
		{
			rightchild = rc;
		}
	}

	//拷贝节点
	BinaryTreeNode<T>* Copy(const BinaryTreeNode<T>* x);

	//销毁以本节点为根的子树
	void Destory()
	{
		if (this != nullptr)
		{
			this->leftchild->Destory();
			this->rightchild->Destory();
			delete this;
		}
	}

	//高度和节点数量
	int height()const;
	int size() const;//以本节点为根的子树的节点数

	//相等性判断
	friend bool equal(const BinaryTreeNode<T>* a, const BinaryTreeNode<T>* b);


	//前中后遍历
	void preOrder() const;//前序遍历
	void InOrder() const;//中序遍历
	void PostOrder() const;//后序遍历
	void levelOrder() const;//层次遍历

private:
	T data;
	BinaryTreeNode<T>* leftchild, *rightchild;
};


template<typename T>
BinaryTreeNode<T>::BinaryTreeNode(const BinaryTreeNode<T>& x)
{
	if (x != *this)
	{
		this->data = x.data;
		BinaryTreeNode<T>* temp = leftchild;
		this->leftchild = x.leftchild;
		delete temp;
		temp = rightchild;
		this->rightchild = x.rightchild;
		delete temp;
		temp = nullptr;
	}

}

template<typename T>
BinaryTreeNode<T>* BinaryTreeNode<T>::Copy(const BinaryTreeNode<T>* x)
{
	if (x == nullptr)
		return nullptr;

	BinaryTreeNode<T>* temp = new BinaryTreeNode<T>(x->data);
	temp->leftchild = Copy(x->leftchild);
	temp->rightchild = Copy(x->rightchild);
	return temp;
}

template<typename T>
int BinaryTreeNode<T>::height() const
{
	if (this != nullptr)
	{
		int lftheight = this->leftchild->height();
		int rhtheight = this->rightchild->height();
		return (1 + lftheight > rhtheight ? lftheight : rightchild);
	}
	return 0;
}

template<typename T>
int BinaryTreeNode<T>::size() const
{
	if (this != nullptr)
	{
		return 1 + this->leftchild->size() + this->rightchild->size();
	}
	return 0;
}

template<typename T>
void BinaryTreeNode<T>::preOrder() const
{
	if (this != nullptr)
	{
		std::cout << "--->" << this.data << std::endl;
		this->leftchild->preOrder();
		this->rightchild->preOrder();
	}
}

template<typename T>
void BinaryTreeNode<T>::InOrder() const
{
	if (this != nullptr)
	{
		this->leftchild->preOrder();
		std::cout << "--->" << this.data << std::endl;
		this->rightchild->preOrder();
	}
}

template<typename T>
void BinaryTreeNode<T>::PostOrder() const
{
	if (this != nullptr)
	{
		this->leftchild->preOrder();
		this->rightchild->preOrder();
		std::cout << "--->" << this.data << std::endl;
	}
}

template<typename T>
void BinaryTreeNode<T>::levelOrder() const
{
	if (this == nullptr)
		return;
	queue<BinaryTreeNode<T>*> nodeQueue;
	nodeQueue.push(this);
	BinaryTreeNode<T>* temp;
	while (!nodeQueue.empty())
	{
		temp = nodeQueue.front();
		std::cout << "--->" << temp.data << std::endl;
		if (temp = temp->Getleftchild())
			nodeQueue.push(temp);
		if (temp = temp->Getrightchild())
			nodeQueue.push(temp);
		nodeQueue.pop();
	}
}

template<typename T>
bool equal(const BinaryTreeNode<T>* a, const BinaryTreeNode<T>* b)
{
	if (a == nullptr && b == nullptr)
		return true;
	if (a == nullptr || b == nullptr)
		return false;
	if (a->data == b->data && equal(a->leftchild, b->leftchild) && equal(a->rightchild, b->rightchild))
		return true;
	return false;
}


#endif