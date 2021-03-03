#pragma once

//��������

#ifndef _maxHBLT_H_
#define _maxHBLT_H_

#include "BinaryTree.h"

template<typename T>
class maxHblt : public BinaryTree<T>
{
public:
	maxHblt() {}
	maxHblt(BinaryTreeNode<T>* x);

	bool empty() const { return BinaryTree<T>::empty(); }
	int size() const { return BinaryTree<T>::size(); }
	const T& top()
	{//��������Ԫ�أ����ڵ����
		if (treeSize == 0)

			return root->element.second;
	}
	void pop();
	void push(const T&);
	void initialize(T*, int);
	void meld(maxHblt<T>& theHblt)
	{//��theHblt�ͱ� Hblt���л��
		meld(root, theHblt.root);
		treeSize += theHblt.treeSize;
		theHblt.root = NULL;  //�����ٺ����ÿգ�
		theHblt.treeSize = 0;
	}
	void output() { postOrder(hbltOutput); cout << endl; }//�������

private:
	void meld(binaryTreeNode<pair<int, T>>* &, binaryTreeNode<pair<int, T>>* &);//�������HBLT�ϲ�
	static void hbltOutput(binaryTreeNode<pair<int, T>>*t)
	{
		cout << t->element.second << " ";
	}
};

#endif