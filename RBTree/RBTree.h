#pragma once

#ifndef _RBTree_H_
#define _RBTree_H_

enum RBTColor { RED, BLACK };

template <class T>
class RBTNode {
public:
	RBTColor color;    // ��ɫ
	T key;            // �ؼ���(��ֵ)
	RBTNode *left;    // ����
	RBTNode *right;    // �Һ���
	RBTNode *parent; // �����

	RBTNode(T value, RBTColor c, RBTNode *p, RBTNode *l, RBTNode *r) :
		key(value), color(c), parent(), left(l), right(r) {}
};

template <class T>
class RBTree {
private:
	RBTNode<T> *mRoot;    // �����

public:
	RBTree();
	~RBTree();

	//���������Բο�һ��������Ķ���
	void preOrder();// ǰ�����"�����"
	void inOrder();	// �������"�����"
	void postOrder();// �������"�����"

	// (�ݹ�ʵ��)����"�����"�м�ֵΪkey�Ľڵ�
	RBTNode<T>* search(T key);
	// (�ǵݹ�ʵ��)����"�����"�м�ֵΪkey�Ľڵ�
	RBTNode<T>* iterativeSearch(T key);
	// ������С��㣺������С���ļ�ֵ��
	T minimum();
	// ��������㣺���������ļ�ֵ��
	T maximum();
	// �ҽ��(x)�ĺ�̽�㡣��������"�����������ֵ���ڸý��"��"��С���"��
	RBTNode<T>* successor(RBTNode<T> *x);
	// �ҽ��(x)��ǰ����㡣��������"�����������ֵС�ڸý��"��"�����"��
	RBTNode<T>* predecessor(RBTNode<T> *x);
	// �����(keyΪ�ڵ��ֵ)���뵽�������
	void insert(T key);
	// ɾ�����(keyΪ�ڵ��ֵ)
	void remove(T key);
	// ���ٺ����
	void destroy();
	// ��ӡ�����
	void print();
private:
	// ǰ�����"�����"
	void preOrder(RBTNode<T>* tree) const;
	// �������"�����"
	void inOrder(RBTNode<T>* tree) const;
	// �������"�����"
	void postOrder(RBTNode<T>* tree) const;

	// (�ݹ�ʵ��)����"�����x"�м�ֵΪkey�Ľڵ�
	RBTNode<T>* search(RBTNode<T>* x, T key) const;
	// (�ǵݹ�ʵ��)����"�����x"�м�ֵΪkey�Ľڵ�
	RBTNode<T>* iterativeSearch(RBTNode<T>* x, T key) const;

	// ������С��㣺����treeΪ�����ĺ��������С��㡣
	RBTNode<T>* minimum(RBTNode<T>* tree);
	// ��������㣺����treeΪ�����ĺ����������㡣
	RBTNode<T>* maximum(RBTNode<T>* tree);

	// �������ο�AVL�Ĳ���
	void leftRotate(RBTNode<T>* &root, RBTNode<T>* x);
	// �������ο�AVL�Ĳ���
	void rightRotate(RBTNode<T>* &root, RBTNode<T>* y);
	// ���뺯��
	void insert(RBTNode<T>* &root, RBTNode<T>* node);
	// ������������
	void insertFixUp(RBTNode<T>* &root, RBTNode<T>* node);
	// ɾ������
	void remove(RBTNode<T>* &root, RBTNode<T> *node);
	// ɾ����������
	void removeFixUp(RBTNode<T>* &root, RBTNode<T> *node, RBTNode<T> *parent);

	// ���ٺ����
	void destroy(RBTNode<T>* &tree);

	// ��ӡ�����
	void print(RBTNode<T>* tree, T key, int direction);

#define rb_parent(r)   ((r)->parent)
#define rb_color(r) ((r)->color)
#define rb_is_red(r)   ((r)->color==RED)
#define rb_is_black(r)  ((r)->color==BLACK)
#define rb_set_black(r)  do { (r)->color = BLACK; } while (0)
#define rb_set_red(r)  do { (r)->color = RED; } while (0)
#define rb_set_parent(r,p)  do { (r)->parent = (p); } while (0)
#define rb_set_color(r,c)  do { (r)->color = (c); } while (0)
};

/*
* �Ժ�����Ľڵ�(x)��������ת
*
* ����ʾ��ͼ(�Խڵ�x��������)��
*      px                              px
*     /                               /
*    x                               y
*   /  \      --(����)-->           / \              
*  lx   y                          x  ry
*     /   \                       /  \
*    ly   ry                     lx  ly
*
*
*/
template <class T>
void RBTree<T>::leftRotate(RBTNode<T>* &root, RBTNode<T>* x)
{
	// ����x���Һ���Ϊy
	RBTNode<T> *y = x->right;

	// �� ��y�����ӡ� ��Ϊ ��x���Һ��ӡ���
	// ���y�����ӷǿգ��� ��x�� ��Ϊ ��y�����ӵĸ��ס�
	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;

	// �� ��x�ĸ��ס� ��Ϊ ��y�ĸ��ס�
	y->parent = x->parent;

	if (x->parent == NULL)
	{
		root = y;            // ��� ��x�ĸ��ס� �ǿսڵ㣬��y��Ϊ���ڵ�
	}
	else
	{
		if (x->parent->left == x)
			x->parent->left = y;    // ��� x�������ڵ�����ӣ���y��Ϊ��x�ĸ��ڵ�����ӡ�
		else
			x->parent->right = y;    // ��� x�������ڵ�����ӣ���y��Ϊ��x�ĸ��ڵ�����ӡ�
	}

	// �� ��x�� ��Ϊ ��y�����ӡ�
	y->left = x;
	// �� ��x�ĸ��ڵ㡱 ��Ϊ ��y��
	x->parent = y;
}


/*
* �Ժ�����Ľڵ�(y)��������ת
*
* ����ʾ��ͼ(�Խڵ�y��������)��
*            py                               py
*           /                                /
*          y                                x
*         /  \      --(����)-->            /  \                     #
*        x   ry                           lx   y
*       / \                                   / \                   #
*      lx  rx                                rx  ry
*
*/
template <class T>
void RBTree<T>::rightRotate(RBTNode<T>* &root, RBTNode<T>* y)
{
	// ����x�ǵ�ǰ�ڵ�����ӡ�
	RBTNode<T> *x = y->left;

	// �� ��x���Һ��ӡ� ��Ϊ ��y�����ӡ���
	// ���"x���Һ���"��Ϊ�յĻ����� ��y�� ��Ϊ ��x���Һ��ӵĸ��ס�
	y->left = x->right;
	if (x->right != NULL)
		x->right->parent = y;

	// �� ��y�ĸ��ס� ��Ϊ ��x�ĸ��ס�
	x->parent = y->parent;

	if (y->parent == NULL)
	{
		root = x;            // ��� ��y�ĸ��ס� �ǿսڵ㣬��x��Ϊ���ڵ�
	}
	else
	{
		if (y == y->parent->right)
			y->parent->right = x;    // ��� y�������ڵ���Һ��ӣ���x��Ϊ��y�ĸ��ڵ���Һ��ӡ�
		else
			y->parent->left = x;    // (y�������ڵ������) ��x��Ϊ��x�ĸ��ڵ�����ӡ�
	}

	// �� ��y�� ��Ϊ ��x���Һ��ӡ�
	x->right = y;

	// �� ��y�ĸ��ڵ㡱 ��Ϊ ��x��
	y->parent = x;
}
#endif

/*
* �������뵽�������
*
* ����˵����
*     root ������ĸ����
*     node ����Ľ��        // ��Ӧ���㷨���ۡ��е�node
*/
template <class T>
void RBTree<T>::insert(RBTNode<T>* &root, RBTNode<T>* node)
{//node��Ҫ����Ľ��

	RBTNode<T> *y = NULL;
	RBTNode<T> *x = root;

	// 1. �����������һ�Ŷ�������������ڵ���ӵ�����������С�
	while (x != NULL)
	{
		y = x;//y��x�ĸ��ڵ㣬x�ǿ��Բ����λ��
		if (node->key < x->key)
			x = x->left;
		else
			x = x->right;
	}

	node->parent = y;
	if (y != NULL)
	{
		if (node->key < y->key)
			y->left = node;
		else
			y->right = node;
	}
	else
		root = node;

	// 2. ���ýڵ����ɫΪ��ɫ
	node->color = RED;

	// 3. ������������Ϊһ�Ŷ��������
	insertFixUp(root, node);
}

/*
* �����(keyΪ�ڵ��ֵ)���뵽�������
*
* ����˵����
*     tree ������ĸ����
*     key ������ļ�ֵ
*/
template <class T>
void RBTree<T>::insert(T key)
{
	RBTNode<T> *z = NULL;

	// ����½����ʧ�ܣ��򷵻ء�
	if ((z = new RBTNode<T>(key, BLACK, NULL, NULL, NULL)) == NULL)
		return;

	insert(mRoot, z);
}

/*
* �����������������
*
* ���������в���ڵ�֮��(ʧȥƽ��)���ٵ��øú�����
* Ŀ���ǽ������������һ�ź������
*
* ����˵����
*     root ������ĸ�
*     node ����Ľ��        // ��Ӧ���㷨���ۡ��е�z
*/
template <class T>
void RBTree<T>::insertFixUp(RBTNode<T>* &root, RBTNode<T>* node)
{
	RBTNode<T> *parent, *gparent;

	// �������ڵ���ڣ����Ҹ��ڵ����ɫ�Ǻ�ɫ��
	while ((parent = rb_parent(node)) && rb_is_red(parent))
	{
		gparent = rb_parent(parent);//��������游���

		//�������ڵ㡱�ǡ��游�ڵ�����ӡ�
		if (parent == gparent->left)
		{
			// Case 1����������ڵ��Ǻ�ɫ
			{
				RBTNode<T> *uncle = gparent->right;
				if (uncle && rb_is_red(uncle))
				{
					rb_set_black(uncle);   //������
					rb_set_black(parent); //���ױ��
					rb_set_red(gparent);  //�游���
					node = gparent;  
					continue;
				}
			}

			// Case 2�����������Ǻ�ɫ���ҵ�ǰ�ڵ����Һ���   //������
			if (parent->right == node)
			{
				RBTNode<T> *tmp;
				leftRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
				//һ�ٲ���ת����Case 3:
			}

			// Case 3�����������Ǻ�ɫ���ҵ�ǰ�ڵ������ӡ�  //ֱ����
			rb_set_black(parent);
			rb_set_red(gparent);
			rightRotate(root, gparent);
		} 
		else//����z�ĸ��ڵ㡱�ǡ�z���游�ڵ���Һ��ӡ�
		{
			// Case 1����������ڵ��Ǻ�ɫ
			{
				RBTNode<T> *uncle = gparent->left;
				if (uncle && rb_is_red(uncle))
				{
					rb_set_black(uncle);
					rb_set_black(parent);
					rb_set_red(gparent);
					node = gparent;
					continue;
				}
			}

			// Case 2�����������Ǻ�ɫ���ҵ�ǰ�ڵ�������
			if (parent->left == node)
			{
				RBTNode<T> *tmp;
				rightRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
				//һ�ٲ���ת����Case 3:
			}

			// Case 3�����������Ǻ�ɫ���ҵ�ǰ�ڵ����Һ��ӡ�
			rb_set_black(parent);
			rb_set_red(gparent);
			leftRotate(root, gparent);
		}
	}
	// �����ڵ���Ϊ��ɫ
	rb_set_black(root);
}

/*
* ɾ�����(node)�������ر�ɾ���Ľ��
*
* ����˵����
*     root ������ĸ����
*     node ɾ���Ľ��
*/
template <class T>
void RBTree<T>::remove(RBTNode<T>* &root, RBTNode<T> *node)//ɾ�����������ڶ���������
{
	RBTNode<T> *child, *parent;
	RBTColor color;

	// ��ɾ���ڵ��"���Һ��Ӷ���Ϊ��"�������
	if ((node->left != NULL) && (node->right != NULL))
	{
		// ��ɾ�ڵ�ĺ�̽ڵ㡣(��Ϊ"ȡ���ڵ�")
		// ������ȡ��"��ɾ�ڵ�"��λ�ã�Ȼ���ٽ�"��ɾ�ڵ�"ȥ����
		RBTNode<T> *replace = node;

		// ��ȡ��̽ڵ�,ѡ������������С��Ԫ�ػ���������������Ԫ��
		replace = replace->right;
		while (replace->left != NULL)
			replace = replace->left;

		// "node�ڵ�"���Ǹ��ڵ�(ֻ�и��ڵ㲻���ڸ��ڵ�)
		if (rb_parent(node))
		{
			if (rb_parent(node)->left == node)//ɾ���Ľ��������
				rb_parent(node)->left = replace;
			else//ɾ���Ľ�����ҽ��
				rb_parent(node)->right = replace;
		}
		else
			// "node�ڵ�"�Ǹ��ڵ㣬���¸��ڵ㡣
			root = replace;

		// child��"ȡ���ڵ�"���Һ��ӣ�Ҳ����Ҫ"�����Ľڵ�"��
		// "ȡ���ڵ�"�϶����������ӣ���Ϊ����һ����̽ڵ㡣
		child = replace->right;
		parent = rb_parent(replace);
		// ����"ȡ���ڵ�"����ɫ
		color = rb_color(replace);

		// "��ɾ���ڵ�"��"���ĺ�̽ڵ�ĸ��ڵ�"
		if (parent == node)
		{
			parent = replace;
		}
		else
		{
			// child��Ϊ��
			if (child) // child��"ȡ���ڵ�"���Һ��ӣ�Ҳ����Ҫ"�����Ľڵ�"��
				rb_set_parent(child, parent);
			parent->left = child;

			replace->right = node->right;
			rb_set_parent(node->right, replace);
		}

		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;

		if (color == BLACK)
			removeFixUp(root, child, parent);

		delete node;
		return;
	}

	if (node->left != NULL)
		child = node->left;
	else
		child = node->right;

	parent = node->parent;
	// ����"ȡ���ڵ�"����ɫ
	color = node->color;

	if (child)
		child->parent = parent;

	// "node�ڵ�"���Ǹ��ڵ�
	if (parent)
	{ 
		if (parent->left == node)
			parent->left = child;
		else
			parent->right = child;
	}
	else
		root = child;

	if (color == BLACK)
		removeFixUp(root, child, parent);
	delete node;
}

/*
* ɾ��������м�ֵΪkey�Ľڵ�
*
* ����˵����
*     tree ������ĸ����
*/
template <class T>
void RBTree<T>::remove(T key)
{
	RBTNode<T> *node;

	// ����key��Ӧ�Ľڵ�(node)���ҵ��Ļ���ɾ���ýڵ�
	if ((node = search(mRoot, key)) != NULL)
		remove(mRoot, node);
}

/*
* �����ɾ����������
*
* �ڴӺ������ɾ������ڵ�֮��(�����ʧȥƽ��)���ٵ��øú�����
* Ŀ���ǽ������������һ�ź������
*
* ����˵����
*     root ������ĸ�
*     node �������Ľڵ�
*/
template <class T>
void RBTree<T>::removeFixUp(RBTNode<T>* &root, RBTNode<T> *node, RBTNode<T> *parent)
{
	RBTNode<T> *other;

	while ((!node || rb_is_black(node)) && node != root)
	{
		if (parent->left == node)
		{
			other = parent->right; //other��x���ֵ�
			if (rb_is_red(other))
			{
				// Case 1: x���ֵ�w�Ǻ�ɫ��  
				rb_set_black(other);
				rb_set_red(parent);
				leftRotate(root, parent);
				other = parent->right;
			}
			if ((!other->left || rb_is_black(other->left)) &&
				(!other->right || rb_is_black(other->right)))
			{
				// Case 2: x���ֵ�w�Ǻ�ɫ����w����������Ҳ���Ǻ�ɫ��  
				rb_set_red(other);
				node = parent;
				parent = rb_parent(node);
			}
			else
			{
				if (!other->right || rb_is_black(other->right))
				{
					// Case 3: x���ֵ�w�Ǻ�ɫ�ģ�����w�������Ǻ�ɫ���Һ���Ϊ��ɫ��   ����Һ�
					rb_set_black(other->left);
					rb_set_red(other);
					rightRotate(root, other);
					other = parent->right;
				}
				// Case 4: x���ֵ�w�Ǻ�ɫ�ģ�����w���Һ����Ǻ�ɫ�ģ�����������ɫ��    �Һ����
				rb_set_color(other, rb_color(parent));
				rb_set_black(parent);
				rb_set_black(other->right);
				leftRotate(root, parent);
				node = root;
				break;
			}
		}
		else // parent->left != node
		{
			other = parent->left;
			if (rb_is_red(other))
			{
				// Case 1: x���ֵ�w�Ǻ�ɫ��  
				rb_set_black(other);
				rb_set_red(parent);
				rightRotate(root, parent);
				other = parent->left;
			}
			if ((!other->left || rb_is_black(other->left)) &&
				(!other->right || rb_is_black(other->right)))
			{
				// Case 2: x���ֵ�w�Ǻ�ɫ����w����������Ҳ���Ǻ�ɫ��  
				rb_set_red(other);
				node = parent;
				parent = rb_parent(node);
			}
			else
			{
				if (!other->left || rb_is_black(other->left))
				{
					// Case 3: x���ֵ�w�Ǻ�ɫ�ģ�����w�������Ǻ�ɫ���Һ���Ϊ��ɫ��  
					rb_set_black(other->right);
					rb_set_red(other);
					leftRotate(root, other);
					other = parent->left;
				}
				// Case 4: x���ֵ�w�Ǻ�ɫ�ģ�����w���Һ����Ǻ�ɫ�ģ�����������ɫ��
				rb_set_color(other, rb_color(parent));
				rb_set_black(parent);
				rb_set_black(other->left);
				rightRotate(root, parent);
				node = root;
				break;
			}
		}
	}
	if (node)
		rb_set_black(node);
}





//�������C++ʵ��(������)

/*
#ifndef RBTREE_H_
#define RBTREE_H_

#include<iostream>
#include<iomanip>
using namespace std;

enum RBTColor { RED, BLACK };

template <class T>
class RBTNode
{
public:
	T key; //�ؼ���
	RBTColor color;//color
	RBTNode *parent;
	RBTNode *left;
	RBTNode *right;
	RBTNode(T value, RBTColor c, RBTNode *p, RBTNode *l, RBTNode *r) :
		key(value), color(c), parent(), left(l), right(r) {}
};

template <class T>
class RBTree
{
private:
	RBTNode<T> *mRoot;
public:
	RBTree();
	~RBTree();
	//ǰ�����
	void preOrder();
	//�������
	void inOrder();
	//�������
	void postOrder();
	//�ݹ�ʵ�ּ�ֵkey �Ĳ���
	RBTNode<T>* search(T key);
	//�ǵݹ�ʵ�ּ�ֵkey�Ĳ���
	RBTNode<T>* iterativeSearch(T key);

	//������С��㣺������С���ļ�ֵ
	T minimum();
	//��������㣺 ���������ļ�ֵ
	T maximum();

	//�ҽ��ĺ�̽��
	RBTNode<T>* successor(RBTNode<T> *x);
	//�ҽ���ǰ�����
	RBTNode<T>* predecessor(RBTNode<T> *x);

	//�������뵽�������
	void insert(T key);

	//ɾ�����
	void remove(T key);

	//���ٺ����
	void destroy();

	//��ӡ�����
	void print();
private:
	//ǰ����������
	void preOrder(RBTNode<T> *root) const;
	//������������
	void inOrder(RBTNode<T> *root) const;
	//������������
	void postOrder(RBTNode<T> *root) const;

	//�ݹ�ʵ�ּ�ֵ�Ĳ���
	RBTNode<T>* search(RBTNode<T> *root, T key) const;
	//�ǵݹ�ʵ�ּ�ֵ�Ĳ���
	RBTNode<T>* iterativeSearch(RBTNode<T> *root, T key) const;

	//������Сֵ���
	RBTNode<T>* minimum(RBTNode<T> *root);
	//�������ֵ���
	RBTNode<T>* maximum(RBTNode<T> *root);

	//����
	void leftRotate(RBTNode<T> *&root, RBTNode<T>* x);
	//����
	void rightRotate(RBTNode<T> *&root, RBTNode<T> *x);
	//���뺯��
	void insert(RBTNode<T> *&root, RBTNode<T>* node);
	//ɾ������
	void remove(RBTNode<T> *&root, RBTNode<T>* node);

	//��������
	void insertFixUp(RBTNode<T> *&root, RBTNode<T>* node);
	//ɾ������
	void removeFixUp(RBTNode<T> *&root, RBTNode<T>* node);

	//���ٺ����
	void destroy(RBTNode<T> *&root);
	//��ӡ�����
	void print(RBTNode<T> *root, T key, int direction);

#define rb_parent(r)   ((r)->parent)
#define rb_color(r) ((r)->color)
#define rb_is_red(r)   ((r)->color==RED)
#define rb_is_black(r)  ((r)->color==BLACK)
#define rb_set_black(r)  do { (r)->color = BLACK; } while (0)
#define rb_set_red(r)  do { (r)->color = RED; } while (0)
#define rb_set_parent(r,p)  do { (r)->parent = (p); } while (0)
#define rb_set_color(r,c)  do { (r)->color = (c); } while (0)
};

template<class T>
RBTree<T>::RBTree() :mRoot(NULL)
{
	mRoot = NULL;
}

template<class T>
RBTree<T>::~RBTree()
{
	destroy();
}

template<class T>
void RBTree<T>::preOrder(RBTNode<T> *tree) const
{
	if (tree)
	{
		cout << tree->key << " ";
		preOrder(tree->left);
		preOrder(tree->right);
	}
}

template<class T>
void RBTree<T>::preOrder()
{
	preOrder(mRoot);
}

template<class T>
void RBTree<T>::inOrder(RBTNode<T> *tree) const
{
	if (tree)
	{
		inOrder(tree->left);
		cout << tree->key << " ";
		inOrder(tree->right);
	}
}

template<class T>
void RBTree<T>::inOrder()
{
	inOrder(mRoot);
}

template<class T>
void RBTree<T>::postOrder(RBTNode<T> *tree) const
{
	if (tree)
	{
		postOrder(tree->left);
		postOrder(tree->right);
		cout << tree->key << " ";
	}
}
template<class T> void RBTree<T>::inOrder() { inOrder(mRoot); } template<class T> void RBTree<T>::postOrder(RBTNode<T> *tree) const { if (tree) { postOrder(tree->left); postOrder(tree->right); cout << tree->key << " "; } } template<class T> void RBTree<T>::postOrder() { postOrder(mRoot); } template<class T> RBTNode<T>* RBTree<T>::search(RBTNode<T> *x, T key) const { if (x == NULL || x->key == key) return x; if (key < x->key) return search(x->left, key); else return search(x->right, key); } template<class T> RBTNode<T>* RBTree<T>::search(T key) { search(mRoot, key); } template<class T> RBTNode<T>* RBTree<T>::iterativeSearch(RBTNode<T> *x, T key) const { while (x&&x->key != key) { if (key < x->key) x = x->left; else x = x->right; } return x; } template<class T> RBTNode<T>* RBTree<T>::iterativeSearch(T key) { iterativeSearch(mRoot, key); } template<class T> RBTNode<T>* RBTree<T>::minimum(RBTNode<T> *tree) { if (tree == NULL) return NULL; while (tree->left) { tree = tree->left; } return tree; } template<class T> T RBTree<T>::minimum() { RBTNode<T> *p = minimum(mRoot); if (p != NULL) return p->key; return (T)NULL; } template<class T> RBTNode<T>* RBTree<T>::maximum(RBTNode<T> *tree) { if (tree == NULL) return NULL; while (tree->right) tree = tree->right; return tree; } template<class T> T RBTree<T>::maximum() { RBTNode<T> *p = maximum(mRoot); if (p != NULL) return p->key; return (T)NULL; } template<class T> RBTNode<T>* RBTree<T>::successor(RBTNode<T> *x) { if (x->right) return minimum(x->right); RBTNode<T> *y = x->parent; while (y&&y->right == x) { x = y; y = y->parent; } return y; } template<class T> RBTNode<T>* RBTree<T>::predecessor(RBTNode<T> *x) { if (x->left) return maximum(x->left); RBTNode<T> *y = x->parent; while (y&&y->left == x) { x = y; y = y->parent; } return y; } template<class T> void RBTree<T>::leftRotate(RBTNode<T> *&root, RBTNode<T> *x) { RBTNode<T> *y = x->right; x->right = y->left; if (y->left) y->left->parent = x; y->parent = x->parent; if (x->parent == NULL) root = y; else { if (x = x->parent->left) x->parent->left = y; else x->parent->right = y; } x->parent = y; y->left = x; } template<class T> void RBTree<T>::rightRotate(RBTNode<T> *&root, RBTNode<T> *x) { RBTNode<T> *y = x->left; x->left = y->right; if (y->right) y->right->parent = x; y->parent = x->parent; if (x->parent == NULL) root = y; else { if (x == x->parent->left) x->parent->left = y; else x->parent->right = y; } y->right = x; x->parent = y; } template<class T> void RBTree<T>::insertFixUp(RBTNode<T> *&root, RBTNode<T>* node) { RBTNode<T> *parent, *gparent; while ((parent = rb_parent(node)) && rb_is_red(parent)) { gparent = rb_parent(parent); if (parent == gparent->left) { RBTNode<T> *uncle = gparent->right; if (uncle&&rb_is_red(uncle)) { rb_set_black(parent); rb_set_black(uncle); rb_set_red(gparent); node = gparent; continue; } else { if (node == parent->right) { leftRotate(root, parent); RBTNode<T> *tmp = parent; parent = node; node = tmp; } rb_set_black(parent); rb_set_red(gparent); rightRotate(root, gparent); } } else { RBTNode<T> *uncle = gparent->left; if (uncle&&rb_is_red(uncle)) { rb_set_black(parent); rb_set_black(uncle); rb_set_red(gparent); node = gparent; continue; } else { if (node == parent->left) { rightRotate(root, parent); RBTNode<T> *tmp = parent; parent = node; node = tmp; } rb_set_black(parent); rb_set_red(gparent); leftRotate(root, gparent); } } } rb_set_black(root); } template <class T> void RBTree<T>::insert(RBTNode<T>* &root, RBTNode<T>* node) {
	RBTNode<T> *y = NULL; RBTNode<T> *x = root; // 1. �����������һ�Ŷ�������������ڵ���ӵ�����������С� while (x != NULL) { y = x; if (node->key < x->key) x = x->left; else x = x->right; } node->parent = y; if (y!=NULL) { if (node->key < y->key) y->left = node; else y->right = node; } else root = node; // 2. ���ýڵ����ɫΪ��ɫ node->color = RED; // 3. ������������Ϊһ�Ŷ�������� insertFixUp(root, node); } template <class T> void RBTree<T>::insert(T key) { RBTNode<T> *z=NULL; // ����½����ʧ�ܣ��򷵻ء� if ((z=new RBTNode<T>(key,BLACK,NULL,NULL,NULL)) == NULL) return ; insert(mRoot, z); } template<class T> void RBTree<T>::removeFixUp(RBTNode<T> *&root,RBTNode<T>* node) { while(node!=root&&rb_is_black(node)) { RBTNode<T> *parent=rb_parent(node); if(node==parent->left) { RBTNode<T> *other=parent->right; if(rb_is_red(other)) { rb_set_black(other); rb_set_red(parent); rightRotate(root,parent); other=parent->right; } if(rb_is_black(other->left)&&rb_is_black(other->right)) { rb_set_red(other); node=parent; parent=rb_parent(node); } else { if(rb_is_black(other->right)) { rb_set_black(other->left); rb_set_red(other); rightRotate(root,other); other=parent->right; } rb_set_color(other,rb_color(parent)); rb_set_black(other->right); rb_set_black(parent); leftRotate(root,parent); node=root; } } else { RBTNode<T> *other=parent->left; if(rb_is_red(other)) { rb_set_black(other); rb_set_red(parent); rightRotate(root,parent); other=parent->left; } if(rb_is_black(other->left)&&rb_is_black(other->right)) { rb_set_red(other); node=parent; parent=rb_parent(node); } else { if(rb_is_black(other->left)) { rb_set_black(other->right); rb_set_red(other); leftRotate(root,other); other=parent->left; } rb_set_color(other,rb_color(parent)); rb_set_black(other->left); rb_set_black(parent); rightRotate(root,parent); node=root; } } } rb_set_black(node); } template<class T> void RBTree<T>::remove(RBTNode<T> *&root,RBTNode<T> *node) { RBTNode<T> *pnode,*rnode; if(node->left==NULL||node->right==NULL) pnode=node; else pnode=successor(node); if(pnode->left) rnode=pnode->left; else rnode=pnode->right; rnode->parent=pnode->parent; if(pnode->parent==NULL) root=rnode; else { if(pnode==pnode->parent->left) pnode->parent->left=rnode; else pnode->parent->right=rnode; } if(node!=pnode) { node->key=pnode->key; } if(pnode->color==BLACK) removeFixUp(root,rnode); delete pnode; return; } template<class T> void RBTree<T>::remove(T key) { RBTNode<T> *node; if((node=search(mRoot,key))!=NULL) remove(mRoot,node); } template<class T> void RBTree<T>::destroy(RBTNode<T> *&tree) { if(tree==NULL) return; if(tree->left!=NULL) return destroy(tree->left); if(tree->right!=NULL) return destroy(tree->left); delete tree; tree=NULL; } template <class T> void RBTree<T>::destroy() { destroy(mRoot); } template<class T> void RBTree<T>::print(RBTNode<T> *tree,T key,int direction) { if(tree!=NULL) { if(direction==0) cout<<setw(2)<<tree->key<<"(B) is root"<<endl; else cout << setw(2) << tree->key << (rb_is_red(tree)?"(R)":"(B)") << " is " << setw(2) << key << "'s " << setw(12) << (direction==1?"right child" : "left child") << endl; print(tree->left, tree->key, -1); print(tree->right,tree->key, 1); } } template<class T> void RBTree<T>::print() { if(mRoot) print(mRoot,mRoot->key,0); } #endif // RBTREE_H_
	template<class T> void RBTree<T>::inOrder() { inOrder(mRoot); } template<class T> void RBTree<T>::postOrder(RBTNode<T> *tree) const { if (tree) { postOrder(tree->left); postOrder(tree->right); cout << tree->key << " "; } } template<class T> void RBTree<T>::postOrder() { postOrder(mRoot); } template<class T> RBTNode<T>* RBTree<T>::search(RBTNode<T> *x, T key) const { if (x == NULL || x->key == key) return x; if (key < x->key) return search(x->left, key); else return search(x->right, key); } template<class T> RBTNode<T>* RBTree<T>::search(T key) { search(mRoot, key); } template<class T> RBTNode<T>* RBTree<T>::iterativeSearch(RBTNode<T> *x, T key) const { while (x&&x->key != key) { if (key < x->key) x = x->left; else x = x->right; } return x; } template<class T> RBTNode<T>* RBTree<T>::iterativeSearch(T key) { iterativeSearch(mRoot, key); } template<class T> RBTNode<T>* RBTree<T>::minimum(RBTNode<T> *tree) { if (tree == NULL) return NULL; while (tree->left) { tree = tree->left; } return tree; } template<class T> T RBTree<T>::minimum() { RBTNode<T> *p = minimum(mRoot); if (p != NULL) return p->key; return (T)NULL; } template<class T> RBTNode<T>* RBTree<T>::maximum(RBTNode<T> *tree) { if (tree == NULL) return NULL; while (tree->right) tree = tree->right; return tree; } template<class T> T RBTree<T>::maximum() { RBTNode<T> *p = maximum(mRoot); if (p != NULL) return p->key; return (T)NULL; } template<class T> RBTNode<T>* RBTree<T>::successor(RBTNode<T> *x) { if (x->right) return minimum(x->right); RBTNode<T> *y = x->parent; while (y&&y->right == x) { x = y; y = y->parent; } return y; } template<class T> RBTNode<T>* RBTree<T>::predecessor(RBTNode<T> *x) { if (x->left) return maximum(x->left); RBTNode<T> *y = x->parent; while (y&&y->left == x) { x = y; y = y->parent; } return y; } template<class T> void RBTree<T>::leftRotate(RBTNode<T> *&root, RBTNode<T> *x) { RBTNode<T> *y = x->right; x->right = y->left; if (y->left) y->left->parent = x; y->parent = x->parent; if (x->parent == NULL) root = y; else { if (x = x->parent->left) x->parent->left = y; else x->parent->right = y; } x->parent = y; y->left = x; } template<class T> void RBTree<T>::rightRotate(RBTNode<T> *&root, RBTNode<T> *x) { RBTNode<T> *y = x->left; x->left = y->right; if (y->right) y->right->parent = x; y->parent = x->parent; if (x->parent == NULL) root = y; else { if (x == x->parent->left) x->parent->left = y; else x->parent->right = y; } y->right = x; x->parent = y; } template<class T> void RBTree<T>::insertFixUp(RBTNode<T> *&root, RBTNode<T>* node) { RBTNode<T> *parent, *gparent; while ((parent = rb_parent(node)) && rb_is_red(parent)) { gparent = rb_parent(parent); if (parent == gparent->left) { RBTNode<T> *uncle = gparent->right; if (uncle&&rb_is_red(uncle)) { rb_set_black(parent); rb_set_black(uncle); rb_set_red(gparent); node = gparent; continue; } else { if (node == parent->right) { leftRotate(root, parent); RBTNode<T> *tmp = parent; parent = node; node = tmp; } rb_set_black(parent); rb_set_red(gparent); rightRotate(root, gparent); } } else { RBTNode<T> *uncle = gparent->left; if (uncle&&rb_is_red(uncle)) { rb_set_black(parent); rb_set_black(uncle); rb_set_red(gparent); node = gparent; continue; } else { if (node == parent->left) { rightRotate(root, parent); RBTNode<T> *tmp = parent; parent = node; node = tmp; } rb_set_black(parent); rb_set_red(gparent); leftRotate(root, gparent); } } } rb_set_black(root); } template <class T> void RBTree<T>::insert(RBTNode<T>* &root, RBTNode<T>* node) {
		RBTNode<T> *y = NULL; RBTNode<T> *x = root; // 1. �����������һ�Ŷ�������������ڵ���ӵ�����������С� while (x != NULL) { y = x; if (node->key < x->key) x = x->left; else x = x->right; } node->parent = y; if (y!=NULL) { if (node->key < y->key) y->left = node; else y->right = node; } else root = node; // 2. ���ýڵ����ɫΪ��ɫ node->color = RED; // 3. ������������Ϊһ�Ŷ�������� insertFixUp(root, node); } template <class T> void RBTree<T>::insert(T key) { RBTNode<T> *z=NULL; // ����½����ʧ�ܣ��򷵻ء� if ((z=new RBTNode<T>(key,BLACK,NULL,NULL,NULL)) == NULL) return ; insert(mRoot, z); } template<class T> void RBTree<T>::removeFixUp(RBTNode<T> *&root,RBTNode<T>* node) { while(node!=root&&rb_is_black(node)) { RBTNode<T> *parent=rb_parent(node); if(node==parent->left) { RBTNode<T> *other=parent->right; if(rb_is_red(other)) { rb_set_black(other); rb_set_red(parent); rightRotate(root,parent); other=parent->right; } if(rb_is_black(other->left)&&rb_is_black(other->right)) { rb_set_red(other); node=parent; parent=rb_parent(node); } else { if(rb_is_black(other->right)) { rb_set_black(other->left); rb_set_red(other); rightRotate(root,other); other=parent->right; } rb_set_color(other,rb_color(parent)); rb_set_black(other->right); rb_set_black(parent); leftRotate(root,parent); node=root; } } else { RBTNode<T> *other=parent->left; if(rb_is_red(other)) { rb_set_black(other); rb_set_red(parent); rightRotate(root,parent); other=parent->left; } if(rb_is_black(other->left)&&rb_is_black(other->right)) { rb_set_red(other); node=parent; parent=rb_parent(node); } else { if(rb_is_black(other->left)) { rb_set_black(other->right); rb_set_red(other); leftRotate(root,other); other=parent->left; } rb_set_color(other,rb_color(parent)); rb_set_black(other->left); rb_set_black(parent); rightRotate(root,parent); node=root; } } } rb_set_black(node); } template<class T> void RBTree<T>::remove(RBTNode<T> *&root,RBTNode<T> *node) { RBTNode<T> *pnode,*rnode; if(node->left==NULL||node->right==NULL) pnode=node; else pnode=successor(node); if(pnode->left) rnode=pnode->left; else rnode=pnode->right; rnode->parent=pnode->parent; if(pnode->parent==NULL) root=rnode; else { if(pnode==pnode->parent->left) pnode->parent->left=rnode; else pnode->parent->right=rnode; } if(node!=pnode) { node->key=pnode->key; } if(pnode->color==BLACK) removeFixUp(root,rnode); delete pnode; return; } template<class T> void RBTree<T>::remove(T key) { RBTNode<T> *node; if((node=search(mRoot,key))!=NULL) remove(mRoot,node); } template<class T> void RBTree<T>::destroy(RBTNode<T> *&tree) { if(tree==NULL) return; if(tree->left!=NULL) return destroy(tree->left); if(tree->right!=NULL) return destroy(tree->left); delete tree; tree=NULL; } template <class T> void RBTree<T>::destroy() { destroy(mRoot); } template<class T> void RBTree<T>::print(RBTNode<T> *tree,T key,int direction) { if(tree!=NULL) { if(direction==0) cout<<setw(2)<<tree->key<<"(B) is root"<<endl; else cout << setw(2) << tree->key << (rb_is_red(tree)?"(R)":"(B)") << " is " << setw(2) << key << "'s " << setw(12) << (direction==1?"right child" : "left child") << endl; print(tree->left, tree->key, -1); print(tree->right,tree->key, 1); } } template<class T> void RBTree<T>::print() { if(mRoot) print(mRoot,mRoot->key,0); } #endif // RBTREE_H_class T>
		void RBTree<T>::postOrder()
		{
			postOrder(mRoot);
		}

		template<class T>
		RBTNode<T>* RBTree<T>::search(RBTNode<T> *x, T key) const
		{
			if (x == NULL || x->key == key)
				return x;
			if (key < x->key)
				return search(x->left, key);
			else
				return search(x->right, key);
		}

		template<class T>
		RBTNode<T>* RBTree<T>::search(T key)
		{
			search(mRoot, key);
		}

		template<class T>
		RBTNode<T>* RBTree<T>::iterativeSearch(RBTNode<T> *x, T key) const
		{
			while (x&&x->key != key)
			{
				if (key < x->key)
					x = x->left;
				else
					x = x->right;
			}
			return x;
		}

		template<class T>
		RBTNode<T>* RBTree<T>::iterativeSearch(T key)
		{
			iterativeSearch(mRoot, key);
		}

		template<class T>
		RBTNode<T>* RBTree<T>::minimum(RBTNode<T> *tree)
		{
			if (tree == NULL)
				return NULL;
			while (tree->left)
			{
				tree = tree->left;
			}
			return tree;
		}

		template<class T>
		T RBTree<T>::minimum()
		{
			RBTNode<T> *p = minimum(mRoot);
			if (p != NULL)
				return p->key;
			return (T)NULL;
		}

		template<class T>
		RBTNode<T>* RBTree<T>::maximum(RBTNode<T> *tree)
		{
			if (tree == NULL)
				return NULL;
			while (tree->right)
				tree = tree->right;
			return tree;
		}

		template<class T>
		T RBTree<T>::maximum()
		{
			RBTNode<T> *p = maximum(mRoot);
			if (p != NULL)
				return p->key;
			return (T)NULL;
		}

		template<class T>
		RBTNode<T>* RBTree<T>::successor(RBTNode<T> *x)
		{
			if (x->right)
				return minimum(x->right);
			RBTNode<T> *y = x->parent;
			while (y&&y->right == x)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}

		template<class T>
		RBTNode<T>* RBTree<T>::predecessor(RBTNode<T> *x)
		{
			if (x->left)
				return maximum(x->left);
			RBTNode<T> *y = x->parent;
			while (y&&y->left == x)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}

		template<class T>
		void RBTree<T>::leftRotate(RBTNode<T> *&root, RBTNode<T> *x)
		{
			RBTNode<T> *y = x->right;
			x->right = y->left;
			if (y->left)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == NULL)
				root = y;
			else
			{
				if (x = x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
			}
			x->parent = y;
			y->left = x;
		}

		template<class T>
		void RBTree<T>::rightRotate(RBTNode<T> *&root, RBTNode<T> *x)
		{
			RBTNode<T> *y = x->left;
			x->left = y->right;
			if (y->right)
				y->right->parent = x;
			y->parent = x->parent;
			if (x->parent == NULL)
				root = y;
			else
			{
				if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
			}
			y->right = x;
			x->parent = y;
		}

		template<class T>
		void RBTree<T>::insertFixUp(RBTNode<T> *&root, RBTNode<T>* node)
		{
			RBTNode<T> *parent, *gparent;
			while ((parent = rb_parent(node)) && rb_is_red(parent))
			{
				gparent = rb_parent(parent);
				if (parent == gparent->left)
				{
					RBTNode<T> *uncle = gparent->right;
					if (uncle&&rb_is_red(uncle))
					{
						rb_set_black(parent);
						rb_set_black(uncle);
						rb_set_red(gparent);
						node = gparent;
						continue;
					}
					else
					{
						if (node == parent->right)
						{
							leftRotate(root, parent);
							RBTNode<T> *tmp = parent;
							parent = node;
							node = tmp;
						}
						rb_set_black(parent);
						rb_set_red(gparent);
						rightRotate(root, gparent);
					}
				}
				else
				{
					RBTNode<T> *uncle = gparent->left;
					if (uncle&&rb_is_red(uncle))
					{
						rb_set_black(parent);
						rb_set_black(uncle);
						rb_set_red(gparent);
						node = gparent;
						continue;
					}
					else
					{
						if (node == parent->left)
						{
							rightRotate(root, parent);
							RBTNode<T> *tmp = parent;
							parent = node;
							node = tmp;
						}
						rb_set_black(parent);
						rb_set_red(gparent);
						leftRotate(root, gparent);
					}
				}
			}
			rb_set_black(root);
		}

		template <class T>
		void RBTree<T>::insert(RBTNode<T>* &root, RBTNode<T>* node)
		{
			RBTNode<T> *y = NULL;
			RBTNode<T> *x = root;

			// 1. �����������һ�Ŷ�������������ڵ���ӵ�����������С�
			while (x != NULL)
			{
				y = x;
				if (node->key < x->key)
					x = x->left;
				else
					x = x->right;
			}
			node->parent = y;
			if (y != NULL)
			{
				if (node->key < y->key)
					y->left = node;
				else
					y->right = node;
			}
			else
				root = node;

			// 2. ���ýڵ����ɫΪ��ɫ
			node->color = RED;

			// 3. ������������Ϊһ�Ŷ��������
			insertFixUp(root, node);
		}


		template <class T>
		void RBTree<T>::insert(T key)
		{
			RBTNode<T> *z = NULL;

			// ����½����ʧ�ܣ��򷵻ء�
			if ((z = new RBTNode<T>(key, BLACK, NULL, NULL, NULL)) == NULL)
				return;

			insert(mRoot, z);
		}

		template<class T>
		void RBTree<T>::removeFixUp(RBTNode<T> *&root, RBTNode<T>* node)
		{
			while (node != root&&rb_is_black(node))
			{
				RBTNode<T> *parent = rb_parent(node);
				if (node == parent->left)
				{
					RBTNode<T> *other = parent->right;
					if (rb_is_red(other))
					{
						rb_set_black(other);
						rb_set_red(parent);
						rightRotate(root, parent);
						other = parent->right;
					}
					if (rb_is_black(other->left) && rb_is_black(other->right))
					{
						rb_set_red(other);
						node = parent;
						parent = rb_parent(node);
					}
					else
					{
						if (rb_is_black(other->right))
						{
							rb_set_black(other->left);
							rb_set_red(other);
							rightRotate(root, other);
							other = parent->right;
						}
						rb_set_color(other, rb_color(parent));
						rb_set_black(other->right);
						rb_set_black(parent);
						leftRotate(root, parent);
						node = root;
					}
				}
				else
				{
					RBTNode<T> *other = parent->left;
					if (rb_is_red(other))
					{
						rb_set_black(other);
						rb_set_red(parent);
						rightRotate(root, parent);
						other = parent->left;
					}
					if (rb_is_black(other->left) && rb_is_black(other->right))
					{
						rb_set_red(other);
						node = parent;
						parent = rb_parent(node);
					}
					else
					{
						if (rb_is_black(other->left))
						{
							rb_set_black(other->right);
							rb_set_red(other);
							leftRotate(root, other);
							other = parent->left;
						}
						rb_set_color(other, rb_color(parent));
						rb_set_black(other->left);
						rb_set_black(parent);
						rightRotate(root, parent);
						node = root;
					}
				}
			}
			rb_set_black(node);
		}

		template<class T>
		void RBTree<T>::remove(RBTNode<T> *&root, RBTNode<T> *node)
		{
			RBTNode<T> *pnode, *rnode;
			if (node->left == NULL || node->right == NULL)
				pnode = node;
			else
				pnode = successor(node);
			if (pnode->left)
				rnode = pnode->left;
			else
				rnode = pnode->right;
			rnode->parent = pnode->parent;
			if (pnode->parent == NULL)
				root = rnode;
			else
			{
				if (pnode == pnode->parent->left)
					pnode->parent->left = rnode;
				else
					pnode->parent->right = rnode;
			}
			if (node != pnode)
			{
				node->key = pnode->key;
			}
			if (pnode->color == BLACK)
				removeFixUp(root, rnode);
			delete pnode;
			return;
		}

		template<class T>
		void RBTree<T>::remove(T key)
		{
			RBTNode<T> *node;
			if ((node = search(mRoot, key)) != NULL)
				remove(mRoot, node);
		}

		template<class T>
		void RBTree<T>::destroy(RBTNode<T> *&tree)
		{
			if (tree == NULL)
				return;
			if (tree->left != NULL)
				return destroy(tree->left);
			if (tree->right != NULL)
				return destroy(tree->left);
			delete tree;
			tree = NULL;
		}

		template <class T>
		void RBTree<T>::destroy()
		{
			destroy(mRoot);
		}

		template<class T>
		void RBTree<T>::print(RBTNode<T> *tree, T key, int direction)
		{
			if (tree != NULL)
			{
				if (direction == 0)
					cout << setw(2) << tree->key << "(B) is root" << endl;
				else
					cout << setw(2) << tree->key << (rb_is_red(tree) ? "(R)" : "(B)") << " is " << setw(2)
					<< key << "'s " << setw(12) << (direction == 1 ? "right child" : "left child") << endl;
				print(tree->left, tree->key, -1);
				print(tree->right, tree->key, 1);
			}
		}

		template<class T>
		void RBTree<T>::print()
		{
			if (mRoot)
				print(mRoot, mRoot->key, 0);
		}
#endif
*/