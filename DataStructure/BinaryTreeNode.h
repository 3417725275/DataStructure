#pragma once


#ifndef _BinaryTreeNode_H
#define _BinaryTreeNode_H

template <typename T>
class BinaryTreeNode
{
	//����
	BinaryTreeNode() :leftchild(nullptr), rightchild(nullptr) {}
	BinaryTreeNode(const T& dt, const BinaryTreeNode<T>* &lc, const BinaryTreeNode<T>* &rc) :data(dt), leftchild(lc), rightchild(rc) {}
	BinaryTreeNode(const T& dt) :BinaryTreeNode(dt, nullptr, nullptr) {}

	//��������
	BinaryTreeNode(const BinaryTreeNode<T> & x);

	//��ȡ��Աֵ
	T GetData() { return this!=nullptr? data:-1; }
	BinaryTreeNode<T>* Getleftchild() const{ return this!=nullptr?leftchild:nullptr; }
	BinaryTreeNode<T>* Getrightchild() const{ return this!=nullptr?rightchild:nullptr }

	//���ó�Աֵ
	void SetData(const T& dt)
	{
		if (this!=nullptr)
		{
			data = dt;
		}
	}
	void Setleftchild(const BinaryTreeNode<T>* &lc)
	{
		if (this!=nullptr)
		{
			leftchild = lc;
		}
	}
	void Setrightchild(const BinaryTreeNode<T>* &rc)
	{
		if (this!=nullptr)
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


private:
	T data;
	BinaryTreeNode<T>* leftchild, *rightchild;
};



template<typename T>
BinaryTreeNode<T>::BinaryTreeNode(const BinaryTreeNode<T>& x)
{
	if (x != *this)
	{
		this->data= x.data;
		BinaryTreeNode<T>* temp = leftchild;
		this->leftchild = x.leftchild;
		delete temp;
		temp = rightchild;
		this->rightchild = x.rightchild;
		delete temp;
		temp = nullptr;
	}

}


#endif