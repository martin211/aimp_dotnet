#include "Stdafx.h"
#include "AimpServiceVisualizations.h"



HRESULT WINAPI AimpServiceVisualizations::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPExtensionEmbeddedVisualization) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    ppvObject = NULL;
    return res;
}

ULONG WINAPI AimpServiceVisualizations::AddRef(void)
{
    return Base::AddRef();
}

ULONG WINAPI AimpServiceVisualizations::Release(void)
{
    return Base::Release();
}
