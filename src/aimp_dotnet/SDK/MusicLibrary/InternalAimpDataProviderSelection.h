/*
 * AIMP DotNet SDK
 *
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 */
 
#pragma once

class InternalAimpDataProviderSelection : public IUnknownInterfaceImpl<IAIMPMLDataProviderSelection>
{
private:
    gcroot<AIMP::SDK::MusicLibrary::IAimpDataProviderSelection^> _instance;
public:
    InternalAimpDataProviderSelection(gcroot<AIMP::SDK::MusicLibrary::IAimpDataProviderSelection^> managedInstance);

    virtual DOUBLE WINAPI GetValueAsFloat(int FieldIndex);

    virtual int WINAPI GetValueAsInt32(int FieldIndex);

    virtual INT64 WINAPI GetValueAsInt64(int FieldIndex);

    virtual WCHAR* WINAPI GetValueAsString(int FieldIndex, int* Length);

    virtual BOOL WINAPI NextRow();

    virtual BOOL WINAPI HasNextPage();

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);
};
