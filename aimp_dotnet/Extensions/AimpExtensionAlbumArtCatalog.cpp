#include "..\Stdafx.h"
#include "AimpExtensionAlbumArtCatalog.h"
#include "..\SDK\PlayList\AimpFileInfo.h"

HRESULT WINAPI AimpExtensionAlbumArtCatalog::GetIcon(HICON *Image)
{
    return S_OK;
}

HRESULT WINAPI AimpExtensionAlbumArtCatalog::GetName(IAIMPString **Name)
{
    IAIMPString *strObject = NULL;
    System::String^ str = _managedinstance->GetName();
    pin_ptr<const WCHAR> strDate = PtrToStringChars(str);
    _aimpCore->CreateObject(IID_IAIMPString, (void**)&strObject);
    strObject->SetData((PWCHAR)strDate, str->Length);
    *Name = strObject;
    return S_OK;
}

HRESULT WINAPI AimpExtensionAlbumArtCatalog::Show(IAIMPString *FileURI, IAIMPString *Artist, IAIMPString *Album, IAIMPImageContainer **Image)
{
    System::Drawing::Bitmap^ bitmap;
    HRESULT r = (HRESULT)_managedinstance->Show(
        gcnew System::String(Artist->GetData()), 
        gcnew System::String(Artist->GetData()), 
        gcnew System::String(Album->GetData()), bitmap);

    return r;
}

HRESULT WINAPI AimpExtensionAlbumArtCatalog::Show2(IAIMPFileInfo *FileInfo, IAIMPImageContainer **Image)
{
    System::Drawing::Bitmap^ bitmap;
    AIMP::SDK::PlayList::IAimpFileInfo ^fi = gcnew AIMP::SDK::AimpFileInfo(FileInfo);
    AIMP::AimpActionResult r = _managedinstance->Show(fi, bitmap);
    if (r == AIMP::AimpActionResult::Ok && bitmap != nullptr)
    {
        IAIMPImageContainer *container;
        Utils::CheckResult(_aimpCore->CreateObject(IID_IAIMPImageContainer, (void**)&container));
        *Image = container;
    }

    // TODO: BUGS at IAimpFileInfo->SetDataSize(), need wait to new virsion of AIMP and SDK
    return E_UNEXPECTED;
}
