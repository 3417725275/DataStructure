#pragma once
//平衡二叉树

#ifndef _AVLTree_H_
#define _AVLTree_H_
#include "BinaryTree.h"

template<typename T>
class AVLTree :public BinaryTree
{
	void insert(const T& elem) { insert(elem, root); }
	void erase(const T& elem) { erase(elem, root); }

	//LL单旋，x是最小不平衡二叉树的根节点,返回新的根
	BinaryTreeNode<T>* LL_rotate(BinaryTreeNode<T>* x);
	//RR单旋，x是最小不平衡二叉树的根节点,返回新的根
	BinaryTreeNode<T>* RR_rotate(BinaryTreeNode<T>* x);
	//LR双旋，x是最小不平衡二叉树的根节点,返回新的根
	BinaryTreeNode<T>* LR_rotate(BinaryTreeNode<T>* x);
	//RL双旋，x是最小不平衡二叉树的根节点,返回新的根
	BinaryTreeNode<T>* RL_rotate(BinaryTreeNode<T>* x);

private:
	//在以x为根的平衡二叉树中插入elem，返回新的根
	BinaryTreeNode<T>* insert(const T& elem, BinaryTreeNode<T>* x);
	//在以x为根的平衡二叉树中删除elem，返回新的根
	BinaryTreeNode<T>* erase(const T& elem, BinaryTreeNode<T>* x);

	BinaryTreeNode<T>* root;

};


template<typename T>
BinaryTreeNode<T>* AVLTree<T>::LL_rotate(BinaryTreeNode<T>* x)
{
	BinaryTreeNode<T>* newroot = x->Getleftchild();
	x->Setleftchild(newroot->Getrightchild());
	newroot->Setrightchild(x);
	return newroot;
}

template<typename T>
BinaryTreeNode<T>* AVLTree<T>::RR_rotate(BinaryTreeNode<T>* x)
{
	BinaryTreeNode<T>* newroot = x->Getrightchild();
	x->Setrightchild(newroot->Getleftchild());
	newroot->Setleftchild(x);
	return newroot;
}

template<typename T>
BinaryTreeNode<T>* AVLTree<T>::LR_rotate(BinaryTreeNode<T>* x)
{
	x->Setleftchild(RR_rotate(x->Getleftchild()));
	return LL_rotate(x);
}

template<typename T>
BinaryTreeNode<T>* AVLTree<T>::RL_rotate(BinaryTreeNode<T>* x)
{
	x->Setrightchild(LL_rotate(x->Getrightchild()));
	return RR_rotate(x);
}

template<typename T>
BinaryTreeNode<T>* AVLTree<T>::insert(const T & elem, BinaryTreeNode<T>* x)
{
	if (x == nullptr)
	{
		x = new BinaryTreeNode<T>(elem);
		return x;
	}
	if (elem == x->GetData())
		return x;
	if (elem < x->GetData())
	{
		x->Setleftchild(insert(elem, x->Getleftchild());
		//插入后是否是平衡二叉树，如果不是，要调整
		if ((x->Getleftchild()->height() - x->Getrightchild()->height()) == 2)
		{
			if (elem < x->Getleftchild()->GetData()) //LL型
				x = LL_rotate(x);
			else   //LR型
				x = LR_rotate(x);
		}
	}
	else
	{
		x->Setrightchild(insert(elem, x->Getrightchild()));
		//插入后是否是平衡二叉树，如果不是，要调整
		if ((x->Getrightchild()->height() - x->Getleftchild()->height()) == 2)
		{
			if (elem < x->Getleftchild()->GetData()) //RL型
				x = RL_rotate(x);
			else  //RR型
				x = RR_rotate(x);
		}
	}
	//插入调整后新的根
	return x;
}

template<typename T>
BinaryTreeNode<T>* AVLTree<T>::erase(const T & elem, BinaryTreeNode<T>* x)
{
	if (x == nullptr)
		return x;


	if (elem < x->GetData())
	{
		//左子树删除引起的不平衡相当于在右子树插入引起的不平衡
		x->Setleftchild(erase(elem, x->Getleftchild()));  //在左子树删除该元素
		if ((x->Getrightchild()->height() - x->Getleftchild()->height()) == 2)
		{
			if (x->Getrightchild()->Getrightchild()->height() > x->Getleftchild()->Getleftchild()->height())
				x = RR_rotate(x);  //RR型
			else  //RL型
				x = RL_rotate(x);
		}
	}
	else if (elem > x->GetData()) //在右子树删除该元素
	{
		//右子树删除引起的不平衡相当于在左子树插入引起的不平衡
		x->Setrightchild(erase(elem, x->Getrightchild()));  //在左子树删除该元素
		if ((x->Getleftchild()->height() - x->Getrightchild()->height()) == 2) //在左子树删除元素后判断左子树是否平衡
		{
			//判断是哪种不平衡
			if (x->Getleftchild()->Getleftchild()->height() > x->Getleftchild()->Getrightchild()->height())
				x = LL_rotate(x);  //LL型
			else  //LR型
				x = LR_rotate(x);
		}
	}
	else  //elem == x->GetData()
	{
		//删除过程要判断
		//1.当前节点是不是叶节点
		//2.删除之后看是否会破坏平衡性
		if (x->Getleftchild() != nullptr && x->Getrightchild() != nullptr)
		{//左右子树均不为空，这里类似于二叉搜索树的删除
		 //如果左子树高就用左子树的最大值代替，右子树高就用右子树的最小值代替

			if (x->Getleftchild()->height() > x->Getrightchild()->height()) //左高
			{
				//在x的左子树中寻找最大的元素(parent) ，也可将右子树的最小元素移到x
				BinaryTreeNode<T> *parent = x, *max = x->Getleftchild(), *temp = nullptr;
				while (temp = max->Getrightchild() != nullptr)
				{
					parent = max;  //左子树最大元素的双亲
					max = temp;  //左子树最大元素
				}
				//将左子树最大元素max移到x，然后在x的左子树中删除max
				x->SetData(max->GetData());
				x->Setleftchild(erase(max->GetData(), x->Getleftchild()));
			}
			else  //右子树高
			{
				//在x的左子树中寻找最大的元素(parent) ，也可将右子树的最小元素移到x
				BinaryTreeNode<T> *parent = x, *min = x->Getrightchild(), *temp = nullptr;
				while (temp = min->Getleftchild() != nullptr)
				{
					parent = min;  //左子树最大元素的双亲
					min = temp;  //左子树最大元素
				}
				//将左子树最大元素min移到x，然后在x的左子树中删除min
				x->SetData(min->GetData());
				x->Setrightchild(erase(min->GetData(), x->Getrightchild()));
			}
		}
		else //左右子树中只有一个为nullptr
		{
			BinaryTreeNode<T>* temp = x;
			if (x->Getleftchild() != nullptr) //左子树不为空
				x = x->Getleftchild();
			else if (x->Getrightchild() != nullptr) //右子树不为空
				x = x->Getrightchild();
			else //左右子树都为空
				x = nullptr;
			delete temp;
		}
	}
	return x; //返回删除了元素elem的根节点x
}

#endif