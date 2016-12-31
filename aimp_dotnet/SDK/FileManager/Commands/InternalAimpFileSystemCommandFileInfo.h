#pragma once

class InternalAimpFileSystemCommandFileInfo : IUnknownInterfaceImpl<IAIMPFileSystemCommandFileInfo>
{
private:
    typedef IUnknownInterfaceImpl<IAIMPFileSystemCommandFileInfo> Base;
    gcroot<AIMP::SDK::FileManager::Commands::IAimpFileSystemCommandFileInfo^> _instance;

public:
    InternalAimpFileSystemCommandFileInfo(gcroot<AIMP::SDK::FileManager::Commands::IAimpFileSystemCommandFileInfo^> instance)
    {
        _instance = instance;
    }

    virtual HRESULT WINAPI GetFileAttrs(IAIMPString* FileName, TAIMPFileAttributes* Attrs)
    {
        AIMP::SDK::FileManager::AimpFileAttributes attr;
        AimpActionResult result = _instance->GetFileAttrs(AIMP::SDK::AimpExtension::GetString(FileName), attr);
        Attrs = new TAIMPFileAttributes();
        Attrs->Attributes = (DWORD)attr.Attributes;
        //Attrs->TimeCreation = attr.TimeCreation->ToOADate();
        //Attrs->TimeLastAccess = attr.TimeLastAccess->ToOADate();
        Attrs->TimeLastWrite = attr.TimeLastWrite.ToOADate();

        return (HRESULT)result;
    }

    virtual HRESULT WINAPI GetFileSize(IAIMPString* FileName, INT64* Size)
    {
        long long size = 0;
        AimpActionResult result = _instance->GetFileSize(AIMP::SDK::AimpExtension::GetString(FileName), size);
        *Size = size;
        return (HRESULT)result;
    }

    virtual HRESULT WINAPI IsFileExists(IAIMPString* FileName)
    {
        return (HRESULT)_instance->IsFileExists(AIMP::SDK::AimpExtension::GetString(FileName));
    }

    virtual ULONG WINAPI AddRef(void)
    {
        return Base::AddRef();
    }

    virtual ULONG WINAPI Release(void)
    {
        return Base::Release();
    }

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
    {
        *ppvObject = NULL;
        if (riid == IID_IAIMPFileSystemCommandFileInfo)
        {
            *ppvObject = this;
            AddRef();
            return S_OK;
        }

        return E_NOINTERFACE;
    }
};
