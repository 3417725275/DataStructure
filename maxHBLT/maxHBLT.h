#pragma once

//最大左高树

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
	{//返回最大的元素，根节点最大
		if (treeSize == 0)

			return root->element.second;
	}
	void pop();
	void push(const T&);
	void initialize(T*, int);
	void meld(maxHblt<T>& theHblt)
	{//将theHblt和本 Hblt进行混合
		meld(root, theHblt.root);
		treeSize += theHblt.treeSize;
		theHblt.root = NULL;  //不销毁后再置空？
		theHblt.treeSize = 0;
	}
	void output() { postOrder(hbltOutput); cout << endl; }//后序遍历

private:
	void meld(binaryTreeNode<pair<int, T>>* &, binaryTreeNode<pair<int, T>>* &);//两颗最大HBLT合并
	static void hbltOutput(binaryTreeNode<pair<int, T>>*t)
	{
		cout << t->element.second << " ";
	}
};

#endif