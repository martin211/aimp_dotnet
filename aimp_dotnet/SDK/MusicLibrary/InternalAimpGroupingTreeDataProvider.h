#pragma once
#include "AimpGroupingTreeSelection.h"

class InternalAimpGroupingTreeDataProvider : public IUnknownInterfaceImpl<IAIMPMLGroupingTreeDataProvider>
{
private:
    gcroot<AIMP::SDK::MusicLibrary::DataStorage::IAimpGroupingTreeDataProvider^> _managedInstance;
public:
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
        IAimpGroupingTreeDataProviderSelection^ dataProviderSelection = gcnew AimpGroupingTreeDataProviderSelection();

        return (HRESULT)_managedInstance->GetData(selection, dataProviderSelection);
    }

    virtual HRESULT WINAPI GetFieldForAlphabeticIndex(IAIMPString** FieldName)
    {
        
    }
};
