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

    InternalAimpGroupingTreeDataProvider(gcroot<AIMP::SDK::MusicLibrary::DataStorage::IAimpGroupingTreeDataProvider^> managedInstance)
    {
        _managedInstance = managedInstance;
        _linkCount = 1;
    }

    virtual HRESULT WINAPI AppendFilter(IAIMPMLDataFilterGroup* Filter, IAIMPMLGroupingTreeSelection* Selection)
    {
        AimpDataFilterGroup^ dataFilterGroup = nullptr;
        IAimpGroupingTreeSelection^ selection = nullptr;

        try
        {
            dataFilterGroup = gcnew AimpDataFilterGroup(Filter);
            selection = gcnew AimpGroupingTreeSelection(Selection);

            AIMP::SDK::AimpActionResult result = _managedInstance->AppendFilter(dataFilterGroup, selection);
            return (HRESULT)S_OK;
        }
        finally
        {
            //Selection->Release();
            //Selection = NULL;
            //Filter->Release();
            //Filter = NULL;

            delete dataFilterGroup;
            delete selection;
        }
    }

    virtual DWORD WINAPI GetCapabilities()
    {
        return (DWORD)_managedInstance->GetCapabilities();
    }

    virtual HRESULT WINAPI GetData(IAIMPMLGroupingTreeSelection* Selection, IAIMPMLGroupingTreeDataProviderSelection** Data)
    {
        IAimpGroupingTreeSelection^ selection = nullptr;
        IAimpGroupingTreeDataProviderSelection^ dataProviderSelection = nullptr;

        try
        {
            selection = gcnew AimpGroupingTreeSelection(Selection);
            AimpActionResult result = _managedInstance->GetData(selection, dataProviderSelection);

            if (result == AimpActionResult::Ok)
            {
                *Data = new InternalAimpGroupingTreeDataProviderSelection(dataProviderSelection);
            }

            return (HRESULT)result;
        }
        finally
        {
            //Selection->Release();
            //Selection = NULL;
            //delete selection;
            //delete dataProviderSelection;
        }
    }

    virtual HRESULT WINAPI GetFieldForAlphabeticIndex(IAIMPString** FieldName)
    {
        System::String^ str;

        AimpActionResult result = _managedInstance->GetFieldForAlphabeticIndex(str);

        if (result == AimpActionResult::Ok)
        {
            *FieldName = AIMP::SDK::AimpExtension::GetAimpString(str);
        }

        return (HRESULT)result;
    }

    virtual ULONG WINAPI AddRef(void)
    {
        System::Diagnostics::Debug::WriteLine("InternalAimpGroupingTreeDataProvider.AddRef");
        _linkCount++;
        return _linkCount;
    }

    virtual ULONG WINAPI Release(void)
    {
        System::Diagnostics::Debug::WriteLine("InternalAimpGroupingTreeDataProvider.Release");
        _linkCount--;

        if (_linkCount == 0)
        {
            delete this;
        }

        return _linkCount;
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
