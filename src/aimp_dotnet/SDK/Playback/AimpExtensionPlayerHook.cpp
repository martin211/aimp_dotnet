#include "Stdafx.h"
#include "AimpExtensionPlayerHook.h"

HRESULT AimpExtensionPlayerHook::OnCheckURL(IAIMPString* url, BOOL* handled)
{
    auto urlString = AimpConverter::ToManagedString(url);
    auto result = _managed->OnCheckURL(*&urlString);
    if (result)
    {
        IAIMPString* str = AimpConverter::ToAimpString(urlString);
        url->SetData(str->GetData(), str->GetLength());
        str->Release();
        str = nullptr;
        *handled = 1;
    }
    else
    {
        *handled = 0;
    }

    return S_OK;
}

HRESULT AimpExtensionPlayerHook::QueryInterface(const IID& riid, LPVOID* ppvObject)
{
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPExtensionPlayerHook)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = nullptr;
    return res;
}

ULONG AimpExtensionPlayerHook::AddRef()
{
    return Base::AddRef();
}

ULONG AimpExtensionPlayerHook::Release()
{
    return Base::Release();
}
