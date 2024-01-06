#include "stdafx.h"
#include "InternalAimpVirtualFile.h"

#include "AimpFileInfo.h"
#include "AimpVirtualFile.h"

InternalAimpVirtualFile::InternalAimpVirtualFile(gcroot<IAimpVirtualFile^> managed) {
    _managed = managed;
}

HRESULT WINAPI InternalAimpVirtualFile::GetValueAsInt32(int PropertyID, int* Value) {
    if (PropertyID == AIMP_VIRTUALFILE_PROPID_INDEXINSET)
        *Value = _managed->IndexInSet;

    return S_OK;
}

HRESULT WINAPI InternalAimpVirtualFile::SetValueAsInt32(int PropertyID, int Value) {
    if (PropertyID == AIMP_VIRTUALFILE_PROPID_INDEXINSET)
        _managed->IndexInSet = Value;

    return S_OK;
}

HRESULT InternalAimpVirtualFile::SetValueAsFloat(int PropertyID, const double Value) {
    if (Value == 0)
        return E_NOTIMPL;

    if (PropertyID == AIMP_VIRTUALFILE_PROPID_CLIPSTART)
        _managed->ClipStart = Value;

    if (PropertyID == AIMP_VIRTUALFILE_PROPID_CLIPFINISH)
        _managed->ClipFinish = Value;

    return S_OK;
}

HRESULT InternalAimpVirtualFile::GetValueAsFloat(int PropertyID, double* Value) {
    *Value = 0;

    if (PropertyID == AIMP_VIRTUALFILE_PROPID_CLIPSTART) {
        double val = _managed->ClipStart;
        if (val == 0)
            return E_NOTIMPL;

        *Value = val;
    }

    if (PropertyID == AIMP_VIRTUALFILE_PROPID_CLIPFINISH) {
        double val = _managed->ClipFinish;
        if (val == 0)
            return E_NOTIMPL;

        *Value = val;
    }

    return S_OK;
}

HRESULT InternalAimpVirtualFile::SetValueAsObject(int PropertyID, IUnknown* Value) {
    if (PropertyID == AIMP_VIRTUALFILE_PROPID_AUDIOSOURCEFILE)
        _managed->AudioSourceFile = AimpConverter::ToManagedString(reinterpret_cast<IAIMPString*>(Value));

    if (PropertyID == AIMP_VIRTUALFILE_PROPID_FILEURI)
        _managed->FileUri = AimpConverter::ToManagedString(reinterpret_cast<IAIMPString*>(Value));

    return S_OK;
}

HRESULT InternalAimpVirtualFile::GetValueAsObject(int PropertyID, const IID& IID, void** Value) {
    if (PropertyID == AIMP_VIRTUALFILE_PROPID_AUDIOSOURCEFILE)
        *Value = AimpConverter::ToAimpString(_managed->AudioSourceFile);

    if (PropertyID == AIMP_VIRTUALFILE_PROPID_FILEURI)
        *Value = AimpConverter::ToAimpString(_managed->FileUri);

    if (PropertyID == AIMP_VIRTUALFILE_PROPID_FILEFORMAT)
        *Value = AimpConverter::ToAimpString(_managed->FileFormat);

    return S_OK;
}

HRESULT InternalAimpVirtualFile::CreateStream(IAIMPStream** Stream) {
    const auto str = _managed->CreateStream();

    if (str->ResultType == ActionResultType::OK) {
        *Stream = safe_cast<AimpStream^>(str->Result)->InternalAimpObject;
        return S_OK;
    }

    return E_NOTIMPL;
}

HRESULT InternalAimpVirtualFile::GetFileInfo(IAIMPFileInfo* Info) {
    const auto fi = gcnew AimpFileInfo(Info);
    const auto res = _managed->GetFileInfo(fi);

    return static_cast<HRESULT>(res->ResultType);
}

boolean InternalAimpVirtualFile::IsExists() {
    return _managed->IsExists();
}

HRESULT InternalAimpVirtualFile::IsInSameStream(IAIMPVirtualFile* VirtualFile) {
    return static_cast<HRESULT>(_managed->IsInSameStream(gcnew AimpVirtualFile(VirtualFile))->ResultType);
}

HRESULT InternalAimpVirtualFile::Synchronize() {
    return static_cast<HRESULT>(_managed->Synchronize()->ResultType);
}


HRESULT WINAPI InternalAimpVirtualFile::QueryInterface(REFIID riid, LPVOID* ppvObject) {
    const HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPVirtualFile) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = nullptr;
    return res;
}

ULONG WINAPI InternalAimpVirtualFile::AddRef(void) {
    return Base::AddRef();
}

ULONG WINAPI InternalAimpVirtualFile::Release(void) {
    return Base::Release();
}
