#pragma once

#include <iostream>
#include <string>

using std::string;

template<typename K> class hash;//ģ������

template<> //ģ��������
class hash<string>
{
public:
	size_t operator()(const string theKey)const
	{//���ַ���ת���ɷǸ�����
		unsigned long hashValue = 0;
		int length = static_cast<int>(theKey.length());
		for (int i = 0; i < length; i++)
		{
			hashValue = 5 * hashValue + theKey.at(i); //char��ʽת����unsigned long
		}
		return size_t(hashValue);
	}
};

template<>
class hash<int>
{
public:
	size_t operator()(const int theKey) const 
	{ return size_t(theKey); }

};

template<>
class hash<long>
{
public:
	size_t operator()(const long theKey)
	{
		return size_t(theKey);
	}
};