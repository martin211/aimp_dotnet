#include "stdafx.h"

#include "AimpDataStorageCommandFindInLibrary.h"

#include "SDK/FileManager/AimpFileInfo.h"
#include "SDK/MusicLibrary/AimpGroupingTreeSelection.h"
#include "SDK/Objects/AimpString.h"

AimpDataStorageCommandFindInLibrary::AimpDataStorageCommandFindInLibrary(gcroot<IAimpDataStorageCommandFindInLibrary^> instance) {
    _instance = instance;
}

HRESULT AimpDataStorageCommandFindInLibrary::Find(IAIMPFileInfo* FileInfo, IAIMPString** GroupingPresetID, IAIMPMLGroupingTreeSelection** GroupingTreeSelection) {
    auto result = _instance->Find(gcnew AimpFileInfo(FileInfo));

    //*GroupingPresetID = static_cast<AimpString^>(result->Result->GroupingPresetID)->InternalAimpObject;
    //*GroupingTreeSelection = static_cast<AimpGroupingTreeSelection^>(result->Result->GroupingTreeSelection)->InternalAimpObject;

    *GroupingPresetID = GET_IUNKNOWN(AimpString, result->Result->GroupingPresetID);
    *GroupingTreeSelection = GET_IUNKNOWN(AimpGroupingTreeSelection, result->Result->GroupingTreeSelection);

    return static_cast<HRESULT>(result->ResultType);
}

HRESULT AimpDataStorageCommandFindInLibrary::QueryInterface(const IID& riid, LPVOID* ppvObject) {
    *ppvObject = nullptr;
    if (riid == IID_IAIMPMLDataStorageCommandFindInLibrary) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}

ULONG AimpDataStorageCommandFindInLibrary::AddRef() {
    return Base::AddRef();
}

ULONG AimpDataStorageCommandFindInLibrary::Release() {
    return Base::Release();
}
