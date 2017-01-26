#include "Stdafx.h"
#include "AimpAlbumArtManager.h"

using namespace AIMP::SDK;

AimpAlbumArtManager::AimpAlbumArtManager(ManagedAimpCore^ core) : AimpBaseManager<IAIMPServiceAlbumArt>(core)
{
}

AimpAlbumArtManager::~AimpAlbumArtManager()
{
    delete _findCallback;
}

bool AimpAlbumArtManager::FindInFiles::get()
{
    IAIMPServiceAlbumArt *service = NULL;
    IAIMPPropertyList *prop = NULL;

    try
    {
        if (GetService(IID_IAIMPServiceAlbumArt, &service) == AimpActionResult::Ok)
        {
            if (service != NULL)
            {
                service->QueryInterface(IID_IAIMPPropertyList, (void**)&prop);
                int val = 0;
                prop->GetValueAsInt32(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES, &val);
                return val != 0;
            }

            return false;
        }
    }
    finally
    {
        service->Release();
        prop->Release();
        service = NULL;
        prop = NULL;
    }

    return false;
}

void AimpAlbumArtManager::FindInFiles::set(bool value)
{
    IAIMPServiceAlbumArt *service = NULL;
    IAIMPPropertyList *prop = NULL;

    try
    {
        if (GetService(IID_IAIMPServiceAlbumArt, &service) == AimpActionResult::Ok)
        {
            if (service != NULL)
            {
                service->QueryInterface(IID_IAIMPPropertyList, (void**)&prop);
                prop->SetValueAsInt32(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES, value);
            }
        }
    }
    finally
    {
        service->Release();
        prop->Release();
        service = NULL;
        prop = NULL;
    }
}

bool AimpAlbumArtManager::FindInInternet::get()
{
    IAIMPServiceAlbumArt *service = NULL;
    IAIMPPropertyList *prop = NULL;

    try
    {
        if (GetService(IID_IAIMPServiceAlbumArt, &service) == AimpActionResult::Ok)
        {
            if (service != NULL)
            {
                service->QueryInterface(IID_IAIMPPropertyList, (void**)&prop);
                int val = 0;
                prop->GetValueAsInt32(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_INTERNET, &val);
                return val != 0;
            }
        }
    }
    finally
    {
        service->Release();
        prop->Release();
        service = NULL;
        prop = NULL;
    }

    return false;
}

void AimpAlbumArtManager::FindInInternet::set(bool value)
{
    IAIMPServiceAlbumArt *service = NULL;
    IAIMPPropertyList *prop = NULL;

    try
    {
        if (GetService(IID_IAIMPServiceAlbumArt, &service) == AimpActionResult::Ok)
        {
            if (service != NULL)
            {
                service->QueryInterface(IID_IAIMPPropertyList, (void**)&prop);
                prop->SetValueAsInt32(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_INTERNET, value ? 1 : 0);
            }
        }
    }
    finally
    {
        service->Release();
        prop->Release();
        service = NULL;
        prop = NULL;
    }
}

array<System::String^>^ AimpAlbumArtManager::FileMasks::get()
{
    IAIMPServiceAlbumArt *service = NULL;
    IAIMPPropertyList *prop = NULL;

    try
    {
        if (GetService(IID_IAIMPServiceAlbumArt, &service) == AimpActionResult::Ok)
        {
            if (service != NULL)
            {
                service->QueryInterface(IID_IAIMPPropertyList, (void**)&prop);
                IAIMPString *str;
                prop->GetValueAsObject(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES_MASKS, IID_IAIMPString, (void**)&str);
                String^ result = gcnew String(str->GetData());
                str->Release();
                return result->Split(gcnew array<WCHAR>{';'});
            }
        }
    }
    finally
    {
        service->Release();
        prop->Release();
        service = NULL;
        prop = NULL;
    }

    return nullptr;
}

void AimpAlbumArtManager::FileMasks::set(array<System::String^>^ val)
{
    IAIMPServiceAlbumArt *service = NULL;
    IAIMPPropertyList *prop = NULL;

    try
    {
        if (GetService(IID_IAIMPServiceAlbumArt, &service) == AimpActionResult::Ok)
        {
            if (service != NULL)
            {
                service->QueryInterface(IID_IAIMPPropertyList, (void**)&prop);
                String^ str;
                for (int i = 0; i < val->Length; i++)
                {
                    str += val[i] + ";";
                }

                IAIMPString *s = AimpConverter::ToAimpString(str);
                prop->SetValueAsObject(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES_MASKS, s);
                s->Release();
            }
        }
    }
    finally
    {
        service->Release();
        prop->Release();
        service = NULL;
        prop = NULL;
    }
}

array<System::String^>^ AimpAlbumArtManager::FileExtensions::get()
{
    IAIMPServiceAlbumArt *service = NULL;
    IAIMPPropertyList *prop = NULL;

    try
    {
        if (GetService(IID_IAIMPServiceAlbumArt, &service) == AimpActionResult::Ok)
        {
            if (service != NULL)
            {
                service->QueryInterface(IID_IAIMPPropertyList, (void**)&prop);
                IAIMPString *str;
                prop->GetValueAsObject(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES_EXTS, IID_IAIMPString, (void**)&str);
                String^ result = gcnew String(str->GetData());
                str->Release();
                return result->Split(gcnew array<WCHAR>{';'});
            }
        }
    }
    finally
    {
        service->Release();
        prop->Release();
        service = NULL;
        prop = NULL;
    }

    return nullptr;
}

void AimpAlbumArtManager::FileExtensions::set(array<System::String^>^ val)
{
    IAIMPServiceAlbumArt *service = NULL;
    IAIMPPropertyList *prop = NULL;

    try
    {
        if (GetService(IID_IAIMPServiceAlbumArt, &service) == AimpActionResult::Ok)
        {
            if (service != NULL)
            {
                service->QueryInterface(IID_IAIMPPropertyList, (void**)&prop);
                String^ str;
                for (int i = 0; i < val->Length; i++)
                {
                    str += val[i] + ";";
                }

                IAIMPString *s = AimpConverter::ToAimpString(str);
                prop->SetValueAsObject(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES_EXTS, s);
                s->Release();
            }
        }
    }
    finally
    {
        service->Release();
        prop->Release();
        service = NULL;
        prop = NULL;
    }
}

int AimpAlbumArtManager::MaxFileSize::get()
{
    IAIMPServiceAlbumArt *service = NULL;
    IAIMPPropertyList *prop = NULL;

    try
    {
        if (GetService(IID_IAIMPServiceAlbumArt, &service) == AimpActionResult::Ok)
        {
            if (service != NULL)
            {
                service->QueryInterface(IID_IAIMPPropertyList, (void**)&prop);
                int val = 0;
                prop->GetValueAsInt32(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_INTERNET_MAX_FILE_SIZE, &val);
                return val > 0;
            }
        }
    }
    finally
    {
        service->Release();
        prop->Release();
        service = NULL;
        prop = NULL;
    }

    return 0;
}

void AimpAlbumArtManager::MaxFileSize::set(int value)
{
    IAIMPServiceAlbumArt *service = NULL;
    IAIMPPropertyList *prop = NULL;

    try
    {
        if (GetService(IID_IAIMPServiceAlbumArt, &service) == AimpActionResult::Ok)
        {
            if (service != NULL)
            {
                service->QueryInterface(IID_IAIMPPropertyList, (void**)&prop);
                prop->SetValueAsInt32(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_INTERNET, value);
            }
        }
    }
    finally
    {
        service->Release();
        prop->Release();
        service = NULL;
        prop = NULL;
    }
}

void AimpAlbumArtManager::OnAlbumArtReceive(IAIMPImage* image, IAIMPImageContainer* image_container, void* user_data)
{
    AimpGetAlbumArtEventArgs^ args = gcnew AimpGetAlbumArtEventArgs();
    if (image == NULL && image_container == NULL)
    {
        Completed(this, args);
        return;
    }

    if (image_container != NULL && image == NULL)
    {
        args->CoverImage = AimpConverter::ToManagedBitmap(image_container);
    }
    else if (image != NULL)
    {
        args->CoverImage = AimpConverter::ToManagedBitmap(image);
    }

    Completed(this, args);
}

IntPtr AimpAlbumArtManager::GetImage(String^ fileUrl, String^ artist, String^ album, AimpFingCovertArtType flags, Object^ userData)
{
    void* taskId;
    _findCallback = gcnew OnFindCoverCallback(this, &AIMP::AimpAlbumArtManager::OnAlbumArtReceive);
    IntPtr thunk = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(_findCallback);
    IAIMPString *sFileUrl = AimpConverter::ToAimpString(fileUrl);
    IAIMPString *sArtist = AimpConverter::ToAimpString(artist);
    IAIMPString *sAlbum = AimpConverter::ToAimpString(album);

    IAIMPServiceAlbumArt *service = NULL;
    try
    {
        if (GetService(IID_IAIMPServiceAlbumArt, &service) == AimpActionResult::Ok)
        {
            service->Get(
                sFileUrl,
                sArtist,
                sAlbum,
                (DWORD)flags,
                (TAIMPServiceAlbumArtReceiveProc(_stdcall *))thunk.ToPointer(),
                reinterpret_cast<void*>(&userData), &taskId);

            return (IntPtr)taskId;
        }
    }
    finally
    {
        service->Release();
        sFileUrl->Release();
        sAlbum->Release();
        sArtist->Release();
        service = NULL;
        sFileUrl = NULL;
        sAlbum = NULL;
        sArtist = NULL;
    }

    return IntPtr::Zero;
}

IntPtr AimpAlbumArtManager::GetImage(AIMP::SDK::FileManager::IAimpFileInfo^ fileInfo, AimpFingCovertArtType flags, Object^ userData)
{
    void* taskId = nullptr;
    _findCallback = gcnew OnFindCoverCallback(this, &AIMP::AimpAlbumArtManager::OnAlbumArtReceive);
    IntPtr thunk = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(_findCallback);
    AimpFileInfo^ fi = (AimpFileInfo^)fileInfo;

    IAIMPServiceAlbumArt *service = NULL;
    try
    {
        if (GetService(IID_IAIMPServiceAlbumArt, &service) == AimpActionResult::Ok)
        {
            service->Get2(
                ((AIMP::SDK::AimpFileInfo^) fileInfo)->InternalAimpObject,
                (DWORD)flags,
                (TAIMPServiceAlbumArtReceiveProc(_stdcall *))thunk.ToPointer(),
                reinterpret_cast<void*>(&userData),
                &taskId);

            return (IntPtr)taskId;
        }
    }
    finally
    {
        service->Release();
        service = NULL;
    }

    return IntPtr::Zero;
}

void AimpAlbumArtManager::Cancel(IntPtr taskId, AimpFingCovertArtType flags)
{
    if (taskId != IntPtr::Zero)
    {
        IAIMPServiceAlbumArt *service = NULL;
        try
        {
            if (GetService(IID_IAIMPServiceAlbumArt, &service) == AimpActionResult::Ok)
            {
                if (service != NULL)
                    service->Cancel((void*)taskId, (DWORD)flags);
            }
        }
        finally
        {
            service->Release();
            service = NULL;
        }
    }
}
