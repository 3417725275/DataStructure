#pragma once
//Æ½ºâ¶þ²æÊ÷

#ifndef _AVLTree_H_
#define _AVLTree_H_
#include "BinaryTree.h"

template<typename T>
class AVLTree :public BinaryTree
{
	void insert(const T& elem);
	void erase(const T& elem);

	BinaryTreeNode<T>* single_rotate_with_left(BinaryTreeNode<T>* pTn);
	BinaryTreeNode<T>* single_rotate_with_right(BinaryTreeNode<T>* pTn);
	BinaryTreeNode<T>* double_rotate_with_left(BinaryTreeNode<T>* pTn);
	BinaryTreeNode<T>* double_rotate_with_right(BinaryTreeNode<T>* pTn);

private:
	BinaryTreeNode<T>* insert(const T& elem, BinaryTreeNode<T>* pTn);
	BinaryTreeNode<T>* erase(const T& elem, BinaryTreeNode<T>* pTn);


};

#endif
