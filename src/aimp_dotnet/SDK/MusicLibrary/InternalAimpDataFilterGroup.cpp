#include "Stdafx.h"
#include "InternalAimpDataFilterGroup.h"

using namespace AIMP::SDK;
using namespace AIMP::SDK::MusicLibrary;
using namespace AIMP::SDK::MusicLibrary::DataFilter;

InternalAimpDataFilterGroup::InternalAimpDataFilterGroup(gcroot<AIMP::SDK::MusicLibrary::DataFilter::IAimpDataFilterGroup^> managed)
{
    _managed = managed;
}

HRESULT WINAPI InternalAimpDataFilterGroup::Add(IUnknown* Field, VARIANT* Value1, VARIANT* Value2, int Operation, IAIMPMLDataFieldFilter** Filter)
{
    AimpActionResult res = AimpActionResult::Fail;

    IAimpDataFieldFilter^ filter = nullptr;
    res = _managed->Add(AimpConverter::ToManagedString((IAIMPString*)Field), AimpConverter::FromVaiant(Value1), AimpConverter::FromVaiant(Value2), (FieldFilterOperationType)Operation, filter);

    if (res == AimpActionResult::Ok && filter != nullptr)
    {
        // todo implement internal IAIMPMLDataFieldFilter
    }

    return (HRESULT)res;
}

HRESULT WINAPI InternalAimpDataFilterGroup::Add2(IUnknown* Field, VARIANT* Values, int Count, IAIMPMLDataFieldFilterByArray** Filter)
{
    AimpActionResult res = AimpActionResult::Fail;
    array<Object^>^ values = gcnew array<Object^>(Count);
    IAimpDataFieldFilterByArray^ filter;
    res = _managed->Add(AimpConverter::ToManagedString((IAIMPString*)Field), values, Count, filter);

    if (res == AimpActionResult::Ok && filter != nullptr)
    {
        // todo implement IAIMPMLDataFieldFilterByArray
    }

    return (HRESULT)res;
}

HRESULT WINAPI InternalAimpDataFilterGroup::AddGroup(IAIMPMLDataFilterGroup** Group)
{
    AimpActionResult res = AimpActionResult::Fail;
    IAimpDataFilterGroup^ group = nullptr;

    res = _managed->AddGroup(group);
    if (res == AimpActionResult::Ok && group != nullptr)
    {
        *Group = new InternalAimpDataFilterGroup(group);
    }

    return (HRESULT)res;
}

HRESULT WINAPI InternalAimpDataFilterGroup::Clear()
{
    return (HRESULT)_managed->Clear();
}

HRESULT WINAPI InternalAimpDataFilterGroup::Delete(int Index)
{
    return (HRESULT)_managed->Delete(Index);
}

HRESULT WINAPI InternalAimpDataFilterGroup::GetChild(int Index, REFIID IID, void **Obj)
{
    AimpActionResult res = AimpActionResult::Fail;

    if (IID == IID_IAIMPMLDataFilterGroup)
    {
        IAimpDataFilterGroup^ group = nullptr;
        res = _managed->GetChild(Index, group);

        if (res == AimpActionResult::Ok && group != nullptr)
        {
            *Obj = new InternalAimpDataFilterGroup(group);
        }
    }

    if (IID == IID_IAIMPMLDataFieldFilter)
    {
        IAimpDataFieldFilter^ filter = nullptr;
        res = _managed->GetChild(Index, filter);

        if (res == AimpActionResult::Ok && filter != nullptr)
        {
            //*Obj = new Interna
        }
    }

    return (HRESULT)res;
}

int WINAPI InternalAimpDataFilterGroup::GetChildCount()
{
    return _managed->GetChildCount();
}

ULONG WINAPI InternalAimpDataFilterGroup::AddRef(void)
{
    return Base::AddRef();
}

ULONG WINAPI InternalAimpDataFilterGroup::Release(void)
{
    return Base::Release();
}

HRESULT WINAPI InternalAimpDataFilterGroup::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPMLDataFilterGroup)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = NULL;
    return res;
}

HRESULT WINAPI InternalAimpDataFilterGroup::GetValueAsInt32(int PropertyID, int *Value)
{
    if (PropertyID == AIMPML_FILTERGROUP_OPERATION)
        *Value = (int)_managed->Operation;

    return S_OK;
}

HRESULT WINAPI InternalAimpDataFilterGroup::SetValueAsInt32(int PropertyID, int Value)
{
    if (PropertyID == AIMPML_FILTERGROUP_OPERATION)
        _managed->Operation = (AIMP::SDK::MusicLibrary::DataFilter::FilterGroupOperationType)Value;

    return S_OK;
}
