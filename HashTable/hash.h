#pragma once

#include <iostream>
#include <string>

using std::string;

template<typename K> class hash;//模板声明

template<> //模板特例化
class hash<string>
{
public:
	size_t operator()(const string theKey)const
	{//将字符串转换成非负整数
		unsigned long hashValue = 0;
		int length = static_cast<int>(theKey.length());
		for (int i = 0; i < length; i++)
		{
			hashValue = 5 * hashValue + theKey.at(i); //char隐式转换成unsigned long
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