// DataStructure.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "BinaryTreeNode.h"
#include "BinaryTree.h"

int main()
{
	BinaryTree<int>tree;
	int init[10] = { 3,6,0,2,8,4,9,1,5,7 };
	for (int i = 0; i < 10; i++) 
	{
		tree.insert(init[i]);
	}

	return 0;
}

