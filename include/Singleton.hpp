/*
@file
@brief		Singleton abstract class
@reference	http://dixq.net/g/sp_02.html
*/

#pragma once


template <typename _T>
class Singleton
{
public:
	static _T* Instance()
	{
		static _T inst;
		return &inst;
	}

protected:
	Singleton(){}
	virtual ~Singleton(){}
	Singleton(const Singleton& r){}
	Singleton& operator=(const Singleton& r){}
};


// EOF