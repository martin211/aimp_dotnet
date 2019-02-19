// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#include "Stdafx.h"
#include "InternalAimpDataProviderSelection.h"

InternalAimpDataProviderSelection::InternalAimpDataProviderSelection(gcroot<AIMP::SDK::MusicLibrary::IAimpDataProviderSelection^> managedInstance)
{
    _instance = managedInstance;
}

DOUBLE WINAPI InternalAimpDataProviderSelection::GetValueAsFloat(int FieldIndex)
{
    return _instance->GetValueAsFloat(FieldIndex);
}

int WINAPI InternalAimpDataProviderSelection::GetValueAsInt32(int FieldIndex)
{
    return _instance->GetValueAsInt32(FieldIndex);
}

INT64 WINAPI InternalAimpDataProviderSelection::GetValueAsInt64(int FieldIndex)
{
    return _instance->GetValueAsInt64(FieldIndex);
}

WCHAR* WINAPI InternalAimpDataProviderSelection::GetValueAsString(int FieldIndex, int* Length)
{
    System::String^ str = _instance->GetValueAsString(FieldIndex);
    pin_ptr<const wchar_t> str1 = PtrToStringChars(str);
    *Length = str->Length;
    return PWCHAR(str1);
}

BOOL WINAPI InternalAimpDataProviderSelection::NextRow()
{
    return _instance->NextRow();
}

BOOL WINAPI InternalAimpDataProviderSelection::HasNextPage()
{
    return _instance->HasNextPage();
}

HRESULT WINAPI InternalAimpDataProviderSelection::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    if (riid == IID_IAIMPMLDataProviderSelection)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}
