//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once

class InternalAimpDataProviderSelection : public IUnknownInterfaceImpl<IAIMPMLDataProviderSelection> {
private:
    gcroot<AIMP::SDK::MusicLibrary::IAimpDataProviderSelection^> _instance;
public:
    InternalAimpDataProviderSelection(gcroot<AIMP::SDK::MusicLibrary::IAimpDataProviderSelection^> managedInstance);

    virtual DOUBLE WINAPI GetValueAsFloat(int FieldIndex);

    virtual int WINAPI GetValueAsInt32(int FieldIndex);

    virtual INT64 WINAPI GetValueAsInt64(int FieldIndex);

    virtual WCHAR* WINAPI GetValueAsString(int FieldIndex, int* Length);

    virtual BOOL WINAPI NextRow();

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);
};
