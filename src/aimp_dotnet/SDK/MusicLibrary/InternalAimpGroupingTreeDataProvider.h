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
#include "AimpGroupingTreeSelection.h"
#include "InternalAimpGroupingTreeDataProviderSelection.h"
#include "AimpDataFilterGroup.h"

class InternalAimpGroupingTreeDataProvider : public IAIMPMLGroupingTreeDataProvider
{
private:
    gcroot<AIMP::SDK::MusicLibrary::DataStorage::IAimpGroupingTreeDataProvider^> _managedInstance;
    ULONG _linkCount;

public:
    typedef IUnknownInterfaceImpl<IAIMPMLGroupingTreeDataProvider> Base;

    InternalAimpGroupingTreeDataProvider(gcroot<AIMP::SDK::MusicLibrary::DataStorage::IAimpGroupingTreeDataProvider^> managedInstance);

    virtual HRESULT WINAPI AppendFilter(IAIMPMLDataFilterGroup* Filter, IAIMPMLGroupingTreeSelection* Selection);

    virtual DWORD WINAPI GetCapabilities();

    virtual HRESULT WINAPI GetData(IAIMPMLGroupingTreeSelection* Selection, IAIMPMLGroupingTreeDataProviderSelection** Data);

    virtual HRESULT WINAPI GetFieldForAlphabeticIndex(IAIMPString** FieldName);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);
};
