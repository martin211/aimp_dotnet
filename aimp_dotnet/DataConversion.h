#pragma once
#include ".\Services\PlayList\AimpPlayListItem.h"

using namespace AIMP::SDK;

public class StaticSingleThreadAllocator 
{
public:
	static inline char* Allocate(int size = 255)
	{
		char* Tmp = CurPtr;
		CurPtr += size;
		return Tmp;
	}
	static inline void Dispose(char* addr)
	{
		CurPtr = min(addr, CurPtr);
	}
private:
	static char* CurPtr;
//	static char* Indexes[100];
//	static int CurID;
	static char allocMem[512*1024];
};

char StaticSingleThreadAllocator::allocMem[512*1024];
char* StaticSingleThreadAllocator::CurPtr = StaticSingleThreadAllocator::allocMem;


public class SystemMemoryAllocator 
{
public:
	static inline char* Allocate(int size = 255)
	{
		return new char[size];
	}
	static inline void Dispose(char* addr)
	{
		delete [] addr;
	}
};

template <class T>
public ref class Singletone
{
protected:
	Singletone() 
	{
		_self = nullptr;
		_refCount = 0;
	}
	virtual ~Singletone() 
	{ 
		_self = nullptr;
	}
public:
	static T^ Instance()
	{
		if(!_self)
	  {
		  _self = gcnew T;
	  }
	  _refCount++;
	  return _self;
	}
	void FreeInst()
	{
		if(--_refCount==0)
			delete this;
	}
private:
	static T^ _self;
	static int _refCount;
};