/* AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
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
