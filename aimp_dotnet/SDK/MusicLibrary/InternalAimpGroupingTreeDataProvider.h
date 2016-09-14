#pragma once
#include "AimpGroupingTreeSelection.h"
#include "AimpGroupingTreeDataProviderSelection.h"
#include "AimpDataFilterGroup.h"

class InternalAimpGroupingTreeDataProvider : public IUnknownInterfaceImpl<IAIMPMLGroupingTreeDataProvider>
{
private:
    gcroot<AIMP::SDK::MusicLibrary::DataStorage::IAimpGroupingTreeDataProvider^> _managedInstance;
    IAIMPCore *_aimpCore;

public:
    typedef IUnknownInterfaceImpl<IAIMPMLGroupingTreeDataProvider> Base;

    InternalAimpGroupingTreeDataProvider(gcroot<AIMP::SDK::MusicLibrary::DataStorage::IAimpGroupingTreeDataProvider^> managedInstance)
    {
        _managedInstance = managedInstance;
    }

    virtual HRESULT WINAPI AppendFilter(IAIMPMLDataFilterGroup* Filter, IAIMPMLGroupingTreeSelection* Selection)
    {
        AimpDataFilterGroup^ dataFilterGroup = gcnew AimpDataFilterGroup(Filter);
        IAimpGroupingTreeSelection^ selection = gcnew AimpGroupingTreeSelection(Selection);

        AIMP::SDK::AimpActionResult result = _managedInstance->AppendFilter(dataFilterGroup, selection);

        return (HRESULT)result;
    }

    virtual DWORD WINAPI GetCapabilities()
    {
        return (DWORD)_managedInstance->GetCapabilities();
    }

    virtual HRESULT WINAPI GetData(IAIMPMLGroupingTreeSelection* Selection, IAIMPMLGroupingTreeDataProviderSelection** Data)
    {
        IAimpGroupingTreeSelection^ selection = gcnew AimpGroupingTreeSelection(Selection);
        IAimpGroupingTreeDataProviderSelection^ dataProviderSelection;

        AimpActionResult result = _managedInstance->GetData(selection, dataProviderSelection);

        return (HRESULT)result;
    }

    virtual HRESULT WINAPI GetFieldForAlphabeticIndex(IAIMPString** FieldName)
    {
        return E_FAIL;
    }

    virtual ULONG WINAPI AddRef(void)
    {
        return Base::AddRef();
    }

    virtual ULONG WINAPI Release(void)
    {
        return Base::Release();
    }

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
    {
        if (!ppvObject)
        {
            return E_POINTER;
        }

        if (riid == IID_IAIMPMLGroupingTreeDataProvider)
        {
            *ppvObject = this;
            AddRef();
            return S_OK;
        }

        return E_NOINTERFACE;
    }
};
