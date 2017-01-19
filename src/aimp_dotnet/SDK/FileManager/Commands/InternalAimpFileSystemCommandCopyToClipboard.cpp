#include "Stdafx.h"
#include "InternalAimpFileSystemCommandCopyToClipboard.h"


InternalAimpFileSystemCommandCopyToClipboard::InternalAimpFileSystemCommandCopyToClipboard(gcroot<IAimpFileSystemCommandCopyToClipboard^> instance)
{
    _instance = instance;
}

HRESULT WINAPI InternalAimpFileSystemCommandCopyToClipboard::CopyToClipboard(IAIMPObjectList* Files)
{
    return (HRESULT)_instance->CopyToClipboard(AIMP::SDK::AimpExtension::ToStringCollection(Files));
}

ULONG WINAPI InternalAimpFileSystemCommandCopyToClipboard::AddRef(void)
{
    return Base::AddRef();
}

ULONG WINAPI InternalAimpFileSystemCommandCopyToClipboard::Release(void)
{
    return Base::Release();
}

HRESULT WINAPI InternalAimpFileSystemCommandCopyToClipboard::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPFileSystemCommandCopyToClipboard)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = NULL;
    return res;
}
