#include "Stdafx.h"
#include "InternalAimpFileSystemCommandOpenFileFolder.h"

using namespace AIMP::SDK;

InternalAimpFileSystemCommandOpenFileFolder::InternalAimpFileSystemCommandOpenFileFolder(gcroot<IAimpFileSystemCommandOpenFileFolder^> instance)
{
    _instance = instance;
}

HRESULT WINAPI InternalAimpFileSystemCommandOpenFileFolder::CanProcess(IAIMPString* FileName)
{
    return (HRESULT)_instance->CanProcess(AimpExtension::GetString(FileName));
}

HRESULT WINAPI InternalAimpFileSystemCommandOpenFileFolder::Process(IAIMPString* FileName)
{
    return (HRESULT)_instance->Process(AimpExtension::GetString(FileName));
}

ULONG WINAPI InternalAimpFileSystemCommandOpenFileFolder::AddRef(void)
{
    return Base::AddRef();
}

ULONG WINAPI InternalAimpFileSystemCommandOpenFileFolder::Release(void)
{
    return Base::Release();
}

HRESULT WINAPI InternalAimpFileSystemCommandOpenFileFolder::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPFileSystemCommandOpenFileFolder)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = NULL;
    return res;
}
