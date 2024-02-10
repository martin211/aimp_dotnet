//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once

class InternalAimpExtensionFileFormat :
    public IUnknownInterfaceImpl<IAIMPExtensionFileFormat> {
private:
    gcroot<FileManager::Extensions::IAimpExtensionFileFormat^> _managedInstance;

public:
    typedef IUnknownInterfaceImpl<IAIMPExtensionFileFormat> Base;

    InternalAimpExtensionFileFormat(
        gcroot<FileManager::Extensions::IAimpExtensionFileFormat^> managedInstance) {
        _managedInstance = managedInstance;
    }

    virtual HRESULT WINAPI GetDescription(IAIMPString** s);
    virtual HRESULT WINAPI GetExtList(IAIMPString** s);
    virtual HRESULT WINAPI GetFlags(DWORD* s);
    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);
    virtual ULONG WINAPI AddRef(void);
    virtual ULONG WINAPI Release(void);
};
