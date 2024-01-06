#pragma once
#include "SDK/AimpPropertyList.h"

class InternalAimpVirtualFile : public IUnknownInterfaceImpl<IAIMPVirtualFile>, public AimpPropertyList
{
private:
    gcroot<IAimpVirtualFile^> _managed;
    IAIMPCore* _core;
public:
    typedef IUnknownInterfaceImpl<IAIMPVirtualFile> Base;

    InternalAimpVirtualFile(gcroot<IAimpVirtualFile^> managed);

    ULONG WINAPI AddRef(void) override;
    ULONG WINAPI Release(void) override;
    HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject) override;

    HRESULT WINAPI GetValueAsInt32(int PropertyID, int* Value) override;
    HRESULT WINAPI SetValueAsInt32(int PropertyID, int Value) override;

    HRESULT WINAPI SetValueAsFloat(int PropertyID, const double Value) override;
    HRESULT WINAPI GetValueAsFloat(int PropertyID, double* Value) override;

    HRESULT WINAPI SetValueAsObject(int PropertyID, IUnknown* Value) override;
    HRESULT WINAPI GetValueAsObject(int PropertyID, const IID& IID, void** Value) override;

    HRESULT WINAPI CreateStream(IAIMPStream** Stream) override;
    HRESULT WINAPI GetFileInfo(IAIMPFileInfo* Info) override;
    boolean WINAPI IsExists() override;
    HRESULT WINAPI IsInSameStream(IAIMPVirtualFile* VirtualFile) override;
    HRESULT WINAPI Synchronize() override;
};
