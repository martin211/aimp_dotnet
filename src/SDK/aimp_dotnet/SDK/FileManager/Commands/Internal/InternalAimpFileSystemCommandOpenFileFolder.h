//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once

using namespace AIMP::SDK::FileManager::Commands;

class InternalAimpFileSystemCommandOpenFileFolder : public IUnknownInterfaceImpl<IAIMPFileSystemCommandOpenFileFolder> {
private:
    typedef IUnknownInterfaceImpl<IAIMPFileSystemCommandOpenFileFolder> Base;
    gcroot<IAimpFileSystemCommandOpenFileFolder^> _instance;

public:
    InternalAimpFileSystemCommandOpenFileFolder(gcroot<IAimpFileSystemCommandOpenFileFolder^> instance);

    virtual HRESULT WINAPI CanProcess(IAIMPString* FileName);

    virtual HRESULT WINAPI Process(IAIMPString* FileName);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);
};
