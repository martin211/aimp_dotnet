//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once

class InternalExtensionTagsProvider : public IUnknownInterfaceImpl<IAIMPExtensionTagsProvider> {
private:
    gcroot<TagEditor::Extensions::IAimpExtensionTagsProvider^> _managed;
public:
    typedef IUnknownInterfaceImpl<IAIMPExtensionTagsProvider> Base;

    explicit InternalExtensionTagsProvider(gcroot<TagEditor::Extensions::IAimpExtensionTagsProvider^> managed) : _managed(managed) {
    }

    virtual HRESULT WINAPI GetName(IAIMPString** source);
    virtual HRESULT WINAPI GetSupportedFields(int* fields, int* count);
    // Commands
    virtual HRESULT WINAPI FindAlbums(IAIMPString* query, IAIMPTaskOwner* owner, IAIMPErrorInfo* errorInfo, TAIMPServiceFindTagsOnlineAlbumInfoReceiveProc* receiveProc, void* receiveProcData);
    virtual HRESULT WINAPI FindTracks(IAIMPFileInfo* albumInfo, IAIMPTaskOwner* owner, IAIMPErrorInfo* errorInfo, IAIMPObjectList** tracksInfo);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);
    virtual ULONG WINAPI AddRef(void);
    virtual ULONG WINAPI Release(void);
};