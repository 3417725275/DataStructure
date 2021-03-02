#pragma once
//二叉搜索树，也称二叉排序树
//树节点除了有指向左右孩子节点的指针，还有一个键值成员，用来排序

#ifndef _BSTree_H
#define _BSTree_H
#include "BinaryTree.h"


template<typename T>
class BSTree :public BinaryTree
{
public:
	//构造函数
	BSTree() :BinaryTree() {}
	BSTree(BinaryTreeNode<T>* x) :BinaryTree(x) {}





};



#endif