#pragma once
//������������Ҳ�ƶ���������
//���ڵ������ָ�����Һ��ӽڵ��ָ�룬����һ����ֵ��Ա����������

#ifndef _BSTree_H
#define _BSTree_H
#include "BinaryTree.h"


template<typename T>
class BSTree :public BinaryTree
{
public:
	//���캯��
	BSTree() :BinaryTree() {}
	BSTree(BinaryTreeNode<T>* x) :BinaryTree(x) {}





};



#endif