#pragma once
//ƽ�������

#ifndef _AVLTree_H_
#define _AVLTree_H_
#include "BinaryTree.h"

template<typename T>
class AVLTree :public BinaryTree
{
	void insert(const T& elem);
	void erase(const T& elem);

	//LL������x����С��ƽ��������ĸ��ڵ�,�����µĸ�
	BinaryTreeNode<T>* LL_rotate(BinaryTreeNode<T>* x);
	//RR������x����С��ƽ��������ĸ��ڵ�,�����µĸ�
	BinaryTreeNode<T>* RR_rotate(BinaryTreeNode<T>* x);
	//LR˫����x����С��ƽ��������ĸ��ڵ�,�����µĸ�
	BinaryTreeNode<T>* LR_rotate(BinaryTreeNode<T>* x);
	//RL˫����x����С��ƽ��������ĸ��ڵ�,�����µĸ�
	BinaryTreeNode<T>* RL_rotate(BinaryTreeNode<T>* x);

private:
	//����xΪ����ƽ��������в���elem�������µĸ�
	BinaryTreeNode<T>* insert(const T& elem, BinaryTreeNode<T>* x);
	//����xΪ����ƽ���������ɾ��elem�������µĸ�
	BinaryTreeNode<T>* erase(const T& elem, BinaryTreeNode<T>* x);

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
		//������Ƿ���ƽ���������������ǣ�Ҫ����
		if ((x->Getleftchild()->height() - x->Getrightchild()->height()) == 2)
		{
			if (elem < x->Getleftchild()->GetData()) //LL��
				x = LL_rotate(x);
			else   //LR��
				x = LR_rotate(x);
		}
	}
	else
	{
		x->Setrightchild(insert(elem, x->Getrightchild()));
		//������Ƿ���ƽ���������������ǣ�Ҫ����
		if ((x->Getrightchild()->height() - x->Getleftchild()->height()) == 2)
		{
			if (elem < x->Getleftchild()->GetData()) //RL��
				x = RL_rotate(x);
			else  //RR��
				x = RR_rotate(x);
		}
	}
	//����������µĸ�
	return x;
}

template<typename T>
BinaryTreeNode<T>* AVLTree<T>::erase(const T & elem, BinaryTreeNode<T>* x)
{
	if (x == nullptr)
		return x;


	if (elem < x->GetData())
	{
		x->Setleftchild(erase(elem, x->Getleftchild()));  //��������ɾ����Ԫ��
		if ((x->Getrightchild()->height() - x->Getleftchild()->height()) == 2)
		{
			if (x->Getrightchild()->Getrightchild()->height() > x->Getleftchild()->Getleftchild()->height())
				x = RR_rotate(x);  //RR��
			else  //RL��
				x = RL_rotate(x);
		}
	}
	else if (elem > x->GetData()) //��������ɾ����Ԫ��
	{
		x->Setrightchild(erase(elem, x->Getrightchild()));  //��������ɾ����Ԫ��
		if ((x->Getleftchild()->height() - x->Getleftchild()->height()) == 2)
		{
			if (x->Getleftchild()->Getleftchild()->height() > x->Getleftchild()->Getrightchild()->height())
				x = LL_rotate(x);  //LL��
			else  //LR��
				x = LR_rotate(x);
		}
	}
	else  //elem == x->GetData()
	{
		if (x->Getleftchild() != nullptr && x->Getrightchild() != nullptr)
		{

		}
		else
		{


		}
	}

	return x;

		else { //elem == pTn->element
			if (pTn->lchild != 0 && pTn->rchild != 0) {
				PBtn ptm = delete_min(pTn->rchild);
				if (ptm == pTn->rchild)
					pTn->rchild = ptm->rchild;
				pTn->element = ptm->element;
				delete ptm;
				--hb_size;
			}
			else {
				PBtn ptm = pTn;
				if (0 == pTn->lchild)
					pTn = pTn->rchild;
				else  //pTn->rchild == 0
					pTn = pTn->lchild;
				delete ptm;
				--hb_size;
			}
		}//end of else(elem == pTn->element)
	}//else
	return pTn;
}

#endif