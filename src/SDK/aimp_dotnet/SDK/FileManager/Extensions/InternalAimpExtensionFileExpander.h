//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once

class InternalAimpExtensionFileExpander : public IUnknownInterfaceImpl<IAIMPExtensionFileExpander> {
private:
    gcroot<FileManager::Extensions::IAimpExtensionFileExpander^> _managedInstance;
    IAIMPCore* _core;

public:
    typedef IUnknownInterfaceImpl<IAIMPExtensionFileExpander> Base;

    InternalAimpExtensionFileExpander(gcroot<FileManager::Extensions::IAimpExtensionFileExpander^> managedInstance, IAIMPCore* core);

    virtual HRESULT WINAPI Expand(IAIMPString* fileName, IAIMPObjectList** list, IAIMPProgressCallback* progressCallback);
    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);
    virtual ULONG WINAPI AddRef(void);
    virtual ULONG WINAPI Release(void);
};
