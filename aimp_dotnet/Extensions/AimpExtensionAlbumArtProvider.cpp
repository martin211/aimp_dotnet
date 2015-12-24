#include "..\Stdafx.h"
#include "AimpExtensionAlbumArtProvider.h"
#include "..\SDK\PlayList\AimpFileInfo.h"

HRESULT WINAPI AimpExtensionAlbumArtProvider::Get(IAIMPString *FileURI, IAIMPString *Artist, IAIMPString *Album, IAIMPPropertyList *Options, IAIMPImageContainer **Image)
{
    System::Drawing::Bitmap ^bitmap;

    if (_managedinstance->Get(
        gcnew System::String(FileURI->GetData()),
        gcnew System::String(Artist->GetData()),
        gcnew System::String(Album->GetData()),
        nullptr,
        bitmap) != AIMP::SDK::AimpActionResult::Ok)
    {
        return E_FAIL;
    }

    return S_OK;
}

DWORD WINAPI AimpExtensionAlbumArtProvider::GetCategory()
{
    return (DWORD)_managedinstance->GetCategory();
}

HRESULT WINAPI AimpExtensionAlbumArtProvider::Get2(IAIMPFileInfo *FileInfo, IAIMPPropertyList *Options, IAIMPImageContainer **Image)
{
    System::Drawing::Bitmap^ bitmap;
    AIMP::SDK::PlayList::IAimpFileInfo ^fi = gcnew AIMP::SDK::AimpFileInfo(FileInfo);
    AIMP::AimpActionResult r = _managedinstance->Get(fi, nullptr, bitmap);
    if (r == AIMP::AimpActionResult::Ok && bitmap != nullptr)
    {
        IAIMPImageContainer *container;
        Utils::CheckResult(_aimpCore->CreateObject(IID_IAIMPImageContainer, (void**)&container));
        *Image = container;
    }

    // TODO: BUGS at IAimpFileInfo->SetDataSize(), need wait to new virsion of AIMP and SDK
    return E_UNEXPECTED;
}
