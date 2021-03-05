#pragma once
//ƽ�������

#ifndef _AVLTree_H_
#define _AVLTree_H_
#include "BinaryTree.h"

template<typename T>
class AVLTree :public BinaryTree
{
	void insert(const T& elem) { insert(elem, root); }
	void erase(const T& elem) { erase(elem, root); }

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
		//������ɾ������Ĳ�ƽ���൱������������������Ĳ�ƽ��
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
		//������ɾ������Ĳ�ƽ���൱������������������Ĳ�ƽ��
		x->Setrightchild(erase(elem, x->Getrightchild()));  //��������ɾ����Ԫ��
		if ((x->Getleftchild()->height() - x->Getrightchild()->height()) == 2) //��������ɾ��Ԫ�غ��ж��������Ƿ�ƽ��
		{
			//�ж������ֲ�ƽ��
			if (x->Getleftchild()->Getleftchild()->height() > x->Getleftchild()->Getrightchild()->height())
				x = LL_rotate(x);  //LL��
			else  //LR��
				x = LR_rotate(x);
		}
	}
	else  //elem == x->GetData()
	{
		//ɾ������Ҫ�ж�
		//1.��ǰ�ڵ��ǲ���Ҷ�ڵ�
		//2.ɾ��֮���Ƿ���ƻ�ƽ����
		if (x->Getleftchild() != nullptr && x->Getrightchild() != nullptr)
		{//������������Ϊ�գ����������ڶ�����������ɾ��
		 //����������߾��������������ֵ���棬�������߾�������������Сֵ����

			if (x->Getleftchild()->height() > x->Getrightchild()->height()) //���
			{
				//��x����������Ѱ������Ԫ��(parent) ��Ҳ�ɽ�����������СԪ���Ƶ�x
				BinaryTreeNode<T> *parent = x, *max = x->Getleftchild(), *temp = nullptr;
				while (temp = max->Getrightchild() != nullptr)
				{
					parent = max;  //���������Ԫ�ص�˫��
					max = temp;  //���������Ԫ��
				}
				//�����������Ԫ��max�Ƶ�x��Ȼ����x����������ɾ��max
				x->SetData(max->GetData());
				x->Setleftchild(erase(max->GetData(), x->Getleftchild()));
			}
			else  //��������
			{
				//��x����������Ѱ������Ԫ��(parent) ��Ҳ�ɽ�����������СԪ���Ƶ�x
				BinaryTreeNode<T> *parent = x, *min = x->Getrightchild(), *temp = nullptr;
				while (temp = min->Getleftchild() != nullptr)
				{
					parent = min;  //���������Ԫ�ص�˫��
					min = temp;  //���������Ԫ��
				}
				//�����������Ԫ��min�Ƶ�x��Ȼ����x����������ɾ��min
				x->SetData(min->GetData());
				x->Setrightchild(erase(min->GetData(), x->Getrightchild()));
			}
		}
		else //����������ֻ��һ��Ϊnullptr
		{
			BinaryTreeNode<T>* temp = x;
			if (x->Getleftchild() != nullptr) //��������Ϊ��
				x = x->Getleftchild();
			else if (x->Getrightchild() != nullptr) //��������Ϊ��
				x = x->Getrightchild();
			else //����������Ϊ��
				x = nullptr;
			delete temp;
		}
	}
	return x; //����ɾ����Ԫ��elem�ĸ��ڵ�x
}

#endif