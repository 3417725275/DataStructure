#pragma once


#ifndef _BinaryTreeNode_H
#define _BinaryTreeNode_H
#include <iostream>


template <typename T>
class BinaryTreeNode
{
public:
	//����
	BinaryTreeNode() :leftchild(nullptr), rightchild(nullptr) {}
	BinaryTreeNode(const T& dt, const BinaryTreeNode<T>* &lc, const BinaryTreeNode<T>* &rc) :data(dt), leftchild(lc), rightchild(rc) {}
	BinaryTreeNode(const T& dt) :BinaryTreeNode(dt, nullptr, nullptr) {}

	//��������
	BinaryTreeNode(const BinaryTreeNode<T> & x);

	//��ȡ��Աֵ
	T GetData() { return this != nullptr ? data : -1; }
	BinaryTreeNode<T>* Getleftchild() const { return this != nullptr ? leftchild : nullptr; }
	BinaryTreeNode<T>* Getrightchild() const { return this != nullptr ? rightchild : nullptr; }

	//���ó�Աֵ
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

	//�����ڵ�
	BinaryTreeNode<T>* Copy(const BinaryTreeNode<T>* x);
	
	//�����Ա��ڵ�Ϊ��������
	void Destory()
	{
		if (this != nullptr)
		{
			this->leftchild->Destory();
			this->rightchild->Destory();
			delete this;
		}
	}

	//�߶Ⱥͽڵ�����
	int height();
	int size();

	//������ж�
	friend bool equal(const BinaryTreeNode<T>* a, const BinaryTreeNode<T>* b);


	//ǰ�к����
	void preOrder();//ǰ�����
	void InOrder();//�������
	void PostOrder();//�������

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
int BinaryTreeNode<T>::height()
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
int BinaryTreeNode<T>::size()
{
	if (this != nullptr)
	{
		return 1 + this->leftchild->size() + this->rightchild->size();
	}
	return 0;
}

template<typename T>
void BinaryTreeNode<T>::preOrder()
{
	if (this != nullptr)
	{
		std::cout << "--->" << this.data << std::endl;
		this->leftchild->preOrder();
		this->rightchild->preOrder();
	}
}

template<typename T>
void BinaryTreeNode<T>::InOrder()
{
	if (this != nullptr)
	{
		this->leftchild->preOrder();
		std::cout << "--->" << this.data << std::endl;
		this->rightchild->preOrder();
	}
}

template<typename T>
void BinaryTreeNode<T>::PostOrder()
{
	if (this != nullptr)
	{
		this->leftchild->preOrder();
		this->rightchild->preOrder();
		std::cout << "--->" << this.data << std::endl;
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