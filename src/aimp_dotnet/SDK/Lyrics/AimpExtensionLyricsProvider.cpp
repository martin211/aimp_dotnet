#include "Stdafx.h"
#include "AimpExtensionLyricsProvider.h"
#include "AimpLyrics.h"
#include "SDK/FileManager/AimpFileInfo.h"
#include "SDK/Threading/AimpTaskOwner.h"


AimpExtensionLyricsProvider::AimpExtensionLyricsProvider(gcroot<AIMP::SDK::Lyrics::IAimpExtensionLyricsProvider^> extension)
{
    _managedExtension = extension;
}

HRESULT AimpExtensionLyricsProvider::Get(IAIMPTaskOwner* owner, IAIMPFileInfo* file_info, DWORD flags,
                                         IAIMPLyrics* lyrics)
{
    const auto result = _managedExtension->Get(
        gcnew AimpTaskOwner(owner),
        gcnew AimpFileInfo(file_info),
        static_cast<Lyrics::LyricsFlags>(flags),
        gcnew AimpLyrics(lyrics));

    return static_cast<HRESULT>(result->ResultType);
}

DWORD AimpExtensionLyricsProvider::GetCategory()
{
    return static_cast<DWORD>(_managedExtension->Category);
}

HRESULT AimpExtensionLyricsProvider::QueryInterface(const IID& riid, LPVOID* ppvObject)
{
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPExtensionLyricsProvider)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = nullptr;
    return res;
}

ULONG AimpExtensionLyricsProvider::AddRef()
{
    return Base::AddRef();
}

ULONG AimpExtensionLyricsProvider::Release()
{
    return Base::Release();
}
