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
    HRESULT r = (HRESULT)_managedinstance->Show(gcnew System::String(Artist->GetData()), gcnew System::String(Artist->GetData()), gcnew System::String(Album->GetData()), bitmap);
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
        System::IO::MemoryStream ^stream;

        try
        {
            _aimpCore->CreateObject(IID_IAIMPImageContainer, (void**)&container);
            stream = gcnew System::IO::MemoryStream();
            bitmap->Save(stream, System::Drawing::Imaging::ImageFormat::Png);
            array<byte> ^buffer = gcnew array<byte>(stream->Length);
            buffer = stream->ToArray();

            pin_ptr<System::Byte> p = &buffer[0];
            unsigned char* pby = p;
            container->SetDataSize(pby);
        }
        finally
        {
            if (stream != nullptr)
            {
                stream->Close();
            }
        }
        bitmap->To
        *Image = container;
    }

    return (HRESULT)r;
}
