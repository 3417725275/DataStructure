#pragma once
//������������Ҳ�ƶ���������
//���ڵ������ָ�����Һ��ӽڵ��ָ�룬����һ����ֵ��Ա����������

//�൱����ԭ�еĶ����������ϼ�������������Ը��ݽڵ��ֵ��Ҳ���������һ����ֵ
//����ֱ���ö������Ľڵ�ֵ��������

#ifndef _BSTree_H
#define _BSTree_H
#include "BinaryTree.h"


template<typename T>
class BSTree :public BinaryTree<T>
{
public:
	//���캯��
	BSTree() :BinaryTree() {}
	BSTree(BinaryTreeNode<T>* x) :BinaryTree(x) {}

	//�������ظ���ͬ������
	//bool empty() const { return BinaryTree::empty(); }
	//int size() const { return BinaryTree::size(); }
	//BinaryTreeNode<T>* find(const T& item) const { return BinaryTree::find(item); }
	//bool insert(const T& item) { return BinaryTree::insert(item); }

	void erase(const T& item);
};


template<typename T>
void BSTree<T>::erase(const T & item)
{
	//���ҹؼ���Ϊitem�Ľڵ�
	BinaryTreeNode<T>*dnode = find(item);
	if (dnode == nullptr)
		return;

	//dnode����������ʱ
	BinaryTreeNode<T>* pleft = dnode->Getleftchild();
	BinaryTreeNode<T>* pright = dnode->Getrightchild();
	if (pleft != nullptr && pright != nullptr)
	{
		//��dnode����������Ѱ������Ԫ��(parent)    ��Ҳ�ɽ�����������СԪ���Ƶ�dnode
		BinaryTreeNode<T> *max = dnode, *s = pleft;
		while (s != nullptr)
		{
			max = s;
			s = s->Getrightchild();
		}

		//�����������Ԫ��max�Ƶ�dnode
		BinaryTreeNode<T>* q = new BinaryTreeNode<T>(max->GetData(), pleft, pright);

		



		delete dnode;
		dnode = nullptr;
	}
}

#endif