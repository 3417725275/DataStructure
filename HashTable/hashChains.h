#pragma once

//链表描述的哈希表，见P256图10-4

#include <iostream>
#include "hash.h"
#include "sortedChain.h"

using std::ostream;
using std::istream;


template<typename K, typename E>
class hashChains 
{
public:
	hashChains(int theDivisor = 11);
	~hashChains() { delete[] table; }
	bool empty() const { return dSize == 0; }
	int size() const { return dSize; }
	pair<const K, E>* find(const K& theKey) const;
	void insert(const pair<const K, E>& thePair);
	void erase(const K& theKey);
	void output(ostream& out) const;

protected:
	sortedChain<K, E>* table;//哈希表
	hash<K> hash; //哈希函数
	int dSize; //哈希表中元素数量
	int divisor; //桶数量
};

template<typename K, typename E>
hashChains<K, E>::hashChains(int theDivisor)
{
	divisor = theDivisor;
	dSize = 0;

	//分配桶，每个桶存放着sortedChain，这是一个链表
	table = new sortedChain<K, E>[divisor];
}

template<typename K, typename E>
pair<const K, E>* hashChains<K, E>::find(const K & theKey) const
{
	return table[hash(theKey) % divisor].find(theKey);
}

template<typename K, typename E>
void hashChains<K, E>::insert(const pair<const K, E>& thePair)
{
	int homeBucket = static_cast<int>(hash(thePair.first) % divisor); //起始桶
	int homeSize = table[homeBucket].size();//起始桶的大小
	table[homeBucket].insert(thePair);
	if (table[homeBucked].size() > homeSize())//插入了新元素，而不是覆盖旧元素
		dSize++;
}

template<typename K, typename E>
void hashChains<K, E>::erase(const K & theKey)
{
	table[hash[theKey] % divisor].erase(theKey);
}

template<typename K, typename E>
void hashChains<K, E>::output(ostream & out) const
{
	for (int i = 0; i < divisor; i++)
	{
		if (table[i].size() == 0)
			cout << i << "号桶是空的" << endl;
		else
			cout << table[i] << endl;
	}
}

template<typename K,typename E>
ostream& operator<<(ostream& out, const hashChains<K, E>& x)
{
	x.output(out);
	return out;
}
