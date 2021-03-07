#pragma once

//��������̽�鷽��ʵ�ֵĹ�ϣ��
#include <iostream>
#include "hash.h"
#include "pairNode.h"

using namespace std;

template<typename K, typename E>
class hashTable
{
public:
	hashTable(int theDivisor = 11);//��ϣ�����ĳ���D
	~hashTable() { delete[] table; }
	bool empty() const { return dSize == 0; }
	int size() const { return dSize; }
	pair<const K, E>* find(const K&) const;
	void insert(const pair<const K, E>&);
	void output(ostream& out)const;

protected:
	int search(const K&)const;
	pair<const K, E>** table;//��ϣ��
	hash<K> hash;//���ؼ�������Tӳ����޷�������
	int dSize; //�ֵ���Ԫ�ض�����
	int divisor; //��ϣ�����ĳ���,Ҳ��Ͱ������
};

template<typename K, typename E>
hashTable<K, E>::hashTable(int theDivisor)
{
	divisor = theDivisor;
	dSize = 0;

	//��ʼ����ϣ��
	table = new pair<const K, E>*[divisor];
	for (int i = 0; i < divisor; i++) //ʱ�临�Ӷ�O(D)
		table[i] = NULL;
}

template<typename K, typename E>
pair<const K, E>* hashTable<K, E>::find(const K &theKey) const
{
	//�������ֵƥ��ļ�ֵ��
	//�ҵ��˷��ظ�Ͱ���ڵ��׽ڵ�
	//�Ҳ�������NULL
	int b = search(theKey);
	if (table[b] == NULL || table[b]->first != theKey)
		return NULL;
	return table[b];
}

template<typename K, typename E>
void hashTable<K, E>::insert(const pair<const K, E>& thePair)
{
	//����ֵ��thePair���뵽�ֵ䵱�У�����йؼ�����ͬ��ֵ�ԣ���ô���Ǿɵ�
	//�����ϣ�����˾��׳��쳣

	//����ƥ��ļ�ֵ�ԣ����û�У����ؿɲ����λ��
	int b = searh(thePair.first);
	if (table[b] == NULL)
	{
		//û���ظ��ļ�ֵ�ԣ������е�Ͱ�ǿյ�
		table[b] = new pair<const K, E>(thePair);
		dSize++;
	}
	else
	{
		if (table[b]->first == thePair.first)
		{
			//�ؼ�����ͬ�����Ǿɵļ�ֵ��
			table[b]->second = thePair.second;
		}
		else
		{
			//Ͱ����
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
			cout <<i<<"��ͰΪ��" << endl;
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
	//�ڹ�ϣ����Ѱ�Ҽ�ֵΪtheKey��Ԫ��
	//����ҵ��ˣ����ظü�ֵ�ԣ����򷵻�һ�����ʵĲ���λ��
	//�ṩ�Ĺ�ϣ��Ӧ����δ������
	int i = static_cast<int> hash(theKey) % divisor;
	int j = i;
	do
	{
		if (table[j] == NULL || table[j]->first == theKey)
			return j;
		j = (j + 1) % divisor;//��һ��Ͱ
	} while (j != i);//ѭ������ʼͰʱ����

	return j; //jҲ�п�������ʼͰ��λ��
}


//���غ���<<
//�˺�����һ��ģ�壬���׼��<<��������
template<typename K,typename E>
ostream& operator<<(ostream& out, const hashTable<K, E>& x)
{
	x.output(out);
	return out;
}