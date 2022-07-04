#pragma once

using namespace AIMP::SDK::MusicLibrary::Extension::Command;

class AimpDataStorageCommandFindInLibrary : IUnknownInterfaceImpl<IAIMPMLDataStorageCommandFindInLibrary> {
private:
    gcroot<IAimpDataStorageCommandFindInLibrary^> _instance;
public:
    typedef IUnknownInterfaceImpl<IAIMPMLDataStorageCommandFindInLibrary> Base;

    AimpDataStorageCommandFindInLibrary(gcroot<IAimpDataStorageCommandFindInLibrary^> instance);

    virtual HRESULT WINAPI Find(IAIMPFileInfo* FileInfo, IAIMPString** GroupingPresetID, IAIMPMLGroupingTreeSelection** GroupingTreeSelection);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);
};