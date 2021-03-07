#pragma once

//基于线性探查方法实现的哈希表
#include <iostream>
#include "hash.h"
#include "pairNode.h"

using namespace std;

template<typename K, typename E>
class hashTable
{
public:
	hashTable(int theDivisor = 11);//哈希函数的除数D
	~hashTable() { delete[] table; }
	bool empty() const { return dSize == 0; }
	int size() const { return dSize; }
	pair<const K, E>* find(const K&) const;
	void insert(const pair<const K, E>&);
	void output(ostream& out)const;

protected:
	int search(const K&)const;
	pair<const K, E>** table;//哈希表
	hash<K> hash;//将关键字类型T映射成无符号整型
	int dSize; //字典中元素对数量
	int divisor; //哈希函数的除数,也是桶的数量
};

template<typename K, typename E>
hashTable<K, E>::hashTable(int theDivisor)
{
	divisor = theDivisor;
	dSize = 0;

	//初始化哈希表
	table = new pair<const K, E>*[divisor];
	for (int i = 0; i < divisor; i++) //时间复杂度O(D)
		table[i] = NULL;
}

template<typename K, typename E>
pair<const K, E>* hashTable<K, E>::find(const K &theKey) const
{
	//查找与键值匹配的键值对
	//找到了返回该桶所在的首节点
	//找不到返回NULL
	int b = search(theKey);
	if (table[b] == NULL || table[b]->first != theKey)
		return NULL;
	return table[b];
}

template<typename K, typename E>
void hashTable<K, E>::insert(const pair<const K, E>& thePair)
{
	//将键值对thePair插入到字典当中，如果有关键字相同键值对，那么覆盖旧的
	//如果哈希表满了就抛出异常

	//查找匹配的键值对，如果没有，返回可插入的位置
	int b = searh(thePair.first);
	if (table[b] == NULL)
	{
		//没有重复的键值对，且现有的桶是空的
		table[b] = new pair<const K, E>(thePair);
		dSize++;
	}
	else
	{
		if (table[b]->first == thePair.first)
		{
			//关键字相同，覆盖旧的键值对
			table[b]->second = thePair.second;
		}
		else
		{
			//桶已满
			return;
		}
	}

}

template<typename K, typename E>
void hashTable<K, E>::output(ostream & out) const
{
	for (int i = 0; i < divisor; i++)
	{
		if (table[i] == NULL)
		{
			cout <<i<<"号桶为空" << endl;
		}
		else
		{
			cout << table[i]->first << " " << table[i]->second << endl;
		}
	}
}

template<typename K, typename E>
int hashTable<K, E>::search(const K &theKey) const
{
	//在哈希表中寻找键值为theKey的元素
	//如果找到了，返回该键值对，否则返回一个合适的插入位置
	//提供的哈希表应该是未存满的
	int i = static_cast<int> hash(theKey) % divisor;
	int j = i;
	do
	{
		if (table[j] == NULL || table[j]->first == theKey)
			return j;
		j = (j + 1) % divisor;//下一个桶
	} while (j != i);//循环到起始桶时结束

	return j; //j也有可能是起始桶的位置
}


//重载函数<<
//此函数是一个模板，与标准库<<构成重载
template<typename K,typename E>
ostream& operator<<(ostream& out, const hashTable<K, E>& x)
{
	x.output(out);
	return out;
}