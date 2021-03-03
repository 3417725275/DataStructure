#pragma once
//������������Ҳ�ƶ���������
//���ڵ������ָ�����Һ��ӽڵ��ָ�룬����һ����ֵ��Ա����������

//�൱����ԭ�еĶ����������ϼ�������������Ը��ݽڵ��ֵ��Ҳ���������һ����ֵ
//����ֱ���ö������Ľڵ�ֵ��������

#ifndef _BSTree_H_
#define _BSTree_H_
#include "BinaryTree.h"


template<typename T>
class BSTree :public BinaryTree<T>
{
public:
	//���캯��
	BSTree() :BinaryTree() {}
	BSTree(BinaryTreeNode<T>* x);

	//�������ظ���ͬ������
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
	//���ҹؼ���Ϊitem�Ľڵ�
	BinaryTreeNode<T>*dNode = find(item);
	if (dNode == nullptr)
		return;
	BinaryTreeNode<T>* pdNode = getParent(dNode);

	//dNode����������ʱ
	BinaryTreeNode<T>* pleft = dNode->Getleftchild();
	BinaryTreeNode<T>* pright = dNode->Getrightchild();
	if (pleft != nullptr && pright != nullptr)
	{
		//��dNode����������Ѱ������Ԫ��(parent)    ��Ҳ�ɽ�����������СԪ���Ƶ�dNode
		BinaryTreeNode<T> *parent = dNode, *max = pleft, *temp;
		while (temp = max->Getrightchild() != nullptr)
		{
			parent = max;  //���������Ԫ�ص�˫��
			max = temp;  //���������Ԫ��
		}

		//�����������Ԫ��max�Ƶ�dNode
		BinaryTreeNode<T>* q = new BinaryTreeNode<T>(max->GetData(), pleft, pright);
		if (pdNode == nullptr) //Ҫɾ���Ľڵ������ĸ��ڵ�
			root = q;
		else if (dNode == pdNode->Getleftchild()) //Ҫɾ������ĳ���������ӽڵ�
			pdNode->Setleftchild(dNode);
		else                         //Ҫɾ������ĳ�������Һ��ӽڵ�
			pdNode->Setrightchild(dNode);

		//�����Ҫ���ƣ����������������������Ԫ����Ҫɾ���ڵ�ĺ��ӽڵ�,P344ͼ14-4(a)�����
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


	//dNode���ֻ��һ������,child����亢��
	BinaryTreeNode<T>* child = pdNode->Getleftchild();
	if (child == nullptr)
		child = pdNode->Getrightchild();
	if (child == nullptr)//����������Ϊ��
	{
		delete pdNode;
		return;
	}

	if (dNode == root)
		root = child;
	else //dNode�����ӻ����Һ���
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