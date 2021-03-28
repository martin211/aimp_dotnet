// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#ifndef apiDeprecated
#define apiDeprecated

#include <windows.h>
#include <unknwn.h>
#include "apiThreading.h"

static const GUID IID_IAIMPServiceSynchronizer = { 0x41494D50, 0x5372, 0x7653, 0x79, 0x6E, 0x63, 0x72, 0x00, 0x00, 0x00, 0x00 };
static const GUID IID_IAIMPServiceThreadPool = { 0x41494D50, 0x5372, 0x7654, 0x68, 0x72, 0x64, 0x50, 0x6F, 0x6F, 0x6C, 0x00 };

class IAIMPServiceSynchronizer : public IUnknown
{
public:
	virtual HRESULT WINAPI ExecuteInMainThread(IAIMPTask* Task, BOOL ExecuteNow) = 0;
};

/* IAIMPServiceThreadPool */

class IAIMPServiceThreadPool : public IUnknown
{
public:
	virtual HRESULT WINAPI Cancel(DWORD_PTR TaskHandle, DWORD Flags) = 0;
	virtual HRESULT WINAPI Execute(IAIMPTask* Task, DWORD_PTR* TaskHandle) = 0;
	virtual HRESULT WINAPI WaitFor(DWORD_PTR TaskHandle) = 0;
};


#endif // !apiDeprecated