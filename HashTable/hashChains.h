#pragma once

//���������Ĺ�ϣ����P256ͼ10-4

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
	sortedChain<K, E>* table;//��ϣ��
	hash<K> hash; //��ϣ����
	int dSize; //��ϣ����Ԫ������
	int divisor; //Ͱ����
};

template<typename K, typename E>
hashChains<K, E>::hashChains(int theDivisor)
{
	divisor = theDivisor;
	dSize = 0;

	//����Ͱ��ÿ��Ͱ�����sortedChain������һ������
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
	int homeBucket = static_cast<int>(hash(thePair.first) % divisor); //��ʼͰ
	int homeSize = table[homeBucket].size();//��ʼͰ�Ĵ�С
	table[homeBucket].insert(thePair);
	if (table[homeBucked].size() > homeSize())//��������Ԫ�أ������Ǹ��Ǿ�Ԫ��
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
			cout << i << "��Ͱ�ǿյ�" << endl;
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
