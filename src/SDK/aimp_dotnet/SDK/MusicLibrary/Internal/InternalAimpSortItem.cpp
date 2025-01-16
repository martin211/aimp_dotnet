#include "stdafx.h"
#include "InternalAimpSortItem.h"

#include <codecvt>

ULONG InternalAimpSortItem::AddRef() {
    return Base::AddRef();
}

ULONG InternalAimpSortItem::Release() {
    return Base::Release();
}

HRESULT InternalAimpSortItem::QueryInterface(const IID& riid, LPVOID* ppvObject) {
    const HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPString) {
        *ppvObject = _str;
        AddRef();
        return S_OK;
    }

    if (riid == IID_IAIMPMLSortDirection)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = nullptr;
    return res;
}

HRESULT InternalAimpSortItem::GetValue(int* Value) {
    *Value = _sortDirection;
    return S_OK;
}

HRESULT InternalAimpSortItem::SetValue(int Value) {
    _sortDirection = Value;
    return S_OK;
}
