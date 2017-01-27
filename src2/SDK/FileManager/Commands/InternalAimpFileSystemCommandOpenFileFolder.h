/*
 * AIMP DotNet SDK
 *
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 */
#pragma once
#include "InternalAimpFileSystemCustomFileCommand.h"

using namespace AIMP::SDK::FileManager::Commands;

class InternalAimpFileSystemCommandOpenFileFolder : public IUnknownInterfaceImpl<IAIMPFileSystemCommandOpenFileFolder>
{
private:
    typedef IUnknownInterfaceImpl<IAIMPFileSystemCommandOpenFileFolder> Base;
    gcroot<AIMP::SDK::FileManager::Commands::IAimpFileSystemCommandOpenFileFolder^> _instance;

public:
    InternalAimpFileSystemCommandOpenFileFolder(gcroot<IAimpFileSystemCommandOpenFileFolder^> instance);

    virtual HRESULT WINAPI CanProcess(IAIMPString* FileName);

    virtual HRESULT WINAPI Process(IAIMPString* FileName);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);
};
