// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

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
    IAIMPServiceAlbumArt* service = nullptr;
    IAIMPPropertyList* prop = nullptr;

    try
    {
        if (GetService(IID_IAIMPServiceAlbumArt, &service) == AimpActionResult::OK && service != nullptr)
        {
            service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
            int val = 0;
            prop->GetValueAsInt32(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES, &val);
            return val != 0;
        }
    }
    finally
    {
        service->Release();
        prop->Release();
        service = nullptr;
        prop = nullptr;
    }

    return false;
}

void AimpAlbumArtManager::FindInFiles::set(bool value)
{
    IAIMPServiceAlbumArt* service = nullptr;
    IAIMPPropertyList* prop = nullptr;

    try
    {
        if (GetService(IID_IAIMPServiceAlbumArt, &service) == AimpActionResult::OK && service != nullptr)
        {
            service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
            prop->SetValueAsInt32(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES, value);
        }
    }
    finally
    {
        service->Release();
        prop->Release();
        service = nullptr;
        prop = nullptr;
    }
}

bool AimpAlbumArtManager::FindInInternet::get()
{
    IAIMPServiceAlbumArt* service = nullptr;
    IAIMPPropertyList* prop = nullptr;

    try
    {
        if (GetService(IID_IAIMPServiceAlbumArt, &service) == AimpActionResult::OK && service != nullptr)
        {
            service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
            int val = 0;
            prop->GetValueAsInt32(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_INTERNET, &val);
            return val != 0;
        }
    }
    finally
    {
        service->Release();
        prop->Release();
        service = nullptr;
        prop = nullptr;
    }

    return false;
}

void AimpAlbumArtManager::FindInInternet::set(bool value)
{
    IAIMPServiceAlbumArt* service = nullptr;
    IAIMPPropertyList* prop = nullptr;

    try
    {
        if (GetService(IID_IAIMPServiceAlbumArt, &service) == AimpActionResult::OK && service != nullptr)
        {
            service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
            prop->SetValueAsInt32(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_INTERNET, value ? 1 : 0);
        }
    }
    finally
    {
        service->Release();
        prop->Release();
        service = nullptr;
        prop = nullptr;
    }
}

array<String^>^ AimpAlbumArtManager::FileMasks::get()
{
    IAIMPServiceAlbumArt* service = nullptr;
    IAIMPPropertyList* prop = nullptr;

    try
    {
        if (GetService(IID_IAIMPServiceAlbumArt, &service) == AimpActionResult::OK && service != nullptr)
        {
            service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
            IAIMPString* str;
            prop->GetValueAsObject(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES_MASKS, IID_IAIMPString,
                                   reinterpret_cast<void**>(&str));
            String^ result = gcnew String(str->GetData());
            str->Release();
            return result->Split(gcnew array<WCHAR>{';'});
        }
    }
    finally
    {
        service->Release();
        prop->Release();
        service = nullptr;
        prop = nullptr;
    }

    return nullptr;
}

void AimpAlbumArtManager::FileMasks::set(array<String^>^ val)
{
    IAIMPServiceAlbumArt* service = nullptr;
    IAIMPPropertyList* prop = nullptr;

    try
    {
        if (GetService(IID_IAIMPServiceAlbumArt, &service) == AimpActionResult::OK && service != nullptr)
        {
            service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
            auto str = String::Empty;
            for (auto i = 0; i < val->Length; i++)
            {
                str += val[i] + ";";
            }

            auto s = AimpConverter::ToAimpString(str);
            prop->SetValueAsObject(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES_MASKS, s);
            s->Release();
            s = nullptr;
        }
    }
    finally
    {
        service->Release();
        prop->Release();
        service = nullptr;
        prop = nullptr;
    }
}

array<String^>^ AimpAlbumArtManager::FileExtensions::get()
{
    IAIMPServiceAlbumArt* service = nullptr;
    IAIMPPropertyList* prop = nullptr;

    try
    {
        if (GetService(IID_IAIMPServiceAlbumArt, &service) == AimpActionResult::OK && service != nullptr)
        {
            service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
            IAIMPString* str;
            prop->GetValueAsObject(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES_EXTS, IID_IAIMPString,
                                   reinterpret_cast<void**>(&str));
            auto result = gcnew String(str->GetData());
            str->Release();
            return result->Split(gcnew array<WCHAR>{';'});
        }
    }
    finally
    {
        service->Release();
        prop->Release();
        service = nullptr;
        prop = nullptr;
    }

    return nullptr;
}

void AimpAlbumArtManager::FileExtensions::set(array<System::String^>^ val)
{
    IAIMPServiceAlbumArt* service = nullptr;
    IAIMPPropertyList* prop = nullptr;

    try
    {
        if (GetService(IID_IAIMPServiceAlbumArt, &service) == AimpActionResult::OK && service != nullptr)
        {
            service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
            auto str = String::Empty;
            for (auto i = 0; i < val->Length; i++)
            {
                str += val[i] + ";";
            }

            auto s = AimpConverter::ToAimpString(str);
            prop->SetValueAsObject(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_FILES_EXTS, s);
            s->Release();
            s = nullptr;
        }
    }
    finally
    {
        service->Release();
        prop->Release();
        service = nullptr;
        prop = nullptr;
    }
}

int AimpAlbumArtManager::MaxFileSize::get()
{
    IAIMPServiceAlbumArt* service = nullptr;
    IAIMPPropertyList* prop = nullptr;

    try
    {
        if (GetService(IID_IAIMPServiceAlbumArt, &service) == AimpActionResult::OK && service != nullptr)
        {
            service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
            int val = 0;
            prop->GetValueAsInt32(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_INTERNET_MAX_FILE_SIZE, &val);
            return val > 0;
        }
    }
    finally
    {
        service->Release();
        prop->Release();
        service = nullptr;
        prop = nullptr;
    }

    return 0;
}

void AimpAlbumArtManager::MaxFileSize::set(int value)
{
    IAIMPServiceAlbumArt* service = nullptr;
    IAIMPPropertyList* prop = nullptr;

    try
    {
        if (GetService(IID_IAIMPServiceAlbumArt, &service) == AimpActionResult::OK && service != nullptr)
        {
            service->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop));
            prop->SetValueAsInt32(AIMP_SERVICE_ALBUMART_PROPID_FIND_IN_INTERNET, value);
        }
    }
    finally
    {
        service->Release();
        prop->Release();
        service = nullptr;
        prop = nullptr;
    }
}

void AimpAlbumArtManager::OnAlbumArtReceive(IAIMPImage* image, IAIMPImageContainer* image_container, void* user_data)
{
    AimpGetAlbumArtEventArgs^ args = gcnew AimpGetAlbumArtEventArgs();
    if (image == nullptr && image_container == nullptr)
    {
        Completed(this, args);
        return;
    }

    if (image_container != nullptr && image == nullptr)
    {
        args->CoverImage = AimpConverter::ToManagedBitmap(image_container);
    }
    else if (image != nullptr)
    {
        args->CoverImage = AimpConverter::ToManagedBitmap(image);
    }

    Completed(this, args);
}

IntPtr AimpAlbumArtManager::GetImage(String^ fileUrl, String^ artist, String^ album, AimpFindCovertArtType flags,
                                     Object^ userData)
{
    void* taskId;
    _findCallback = gcnew OnFindCoverCallback(this, &AIMP::AimpAlbumArtManager::OnAlbumArtReceive);
    IntPtr thunk = Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(_findCallback);
    auto sFileUrl = AimpConverter::ToAimpString(fileUrl);
    auto sArtist = AimpConverter::ToAimpString(artist);
    auto sAlbum = AimpConverter::ToAimpString(album);

    IAIMPServiceAlbumArt* service = nullptr;
    try
    {
        if (GetService(IID_IAIMPServiceAlbumArt, &service) == AimpActionResult::OK && service != nullptr)
        {
            service->Get(
                sFileUrl,
                sArtist,
                sAlbum,
                DWORD(flags),
                static_cast<TAIMPServiceAlbumArtReceiveProc(_stdcall *)>(thunk.ToPointer()),
                reinterpret_cast<void*>(&userData), &taskId);

            return IntPtr(taskId);
        }
    }
    finally
    {
        service->Release();
        sFileUrl->Release();
        sAlbum->Release();
        sArtist->Release();
        service = nullptr;
        sFileUrl = nullptr;
        sAlbum = nullptr;
        sArtist = nullptr;
    }

    return IntPtr::Zero;
}

IntPtr AimpAlbumArtManager::GetImage(IAimpFileInfo^ fileInfo, AimpFindCovertArtType flags, Object^ userData)
{
    void* taskId = nullptr;
    _findCallback = gcnew OnFindCoverCallback(this, &AIMP::AimpAlbumArtManager::OnAlbumArtReceive);
    IntPtr thunk = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(_findCallback);
    //AimpFileInfo^ fi = static_cast<AimpFileInfo^>(fileInfo);

    IAIMPServiceAlbumArt* service = nullptr;
    try
    {
        if (GetService(IID_IAIMPServiceAlbumArt, &service) == AimpActionResult::OK && service != nullptr)
        {
            service->Get2(
                static_cast<AimpFileInfo^>(fileInfo)->InternalAimpObject,
                DWORD(flags),
                static_cast<TAIMPServiceAlbumArtReceiveProc(_stdcall *)>(thunk.ToPointer()),
                reinterpret_cast<void*>(&userData),
                &taskId);

            return IntPtr(taskId);
        }
    }
    finally
    {
        service->Release();
        service = nullptr;
    }

    return IntPtr::Zero;
}

void AimpAlbumArtManager::Cancel(IntPtr taskId, AimpFindCovertArtType flags)
{
    if (taskId != IntPtr::Zero)
    {
        IAIMPServiceAlbumArt* service = nullptr;
        try
        {
            if (GetService(IID_IAIMPServiceAlbumArt, &service) == AimpActionResult::OK && service != nullptr)
            {
                service->Cancel(static_cast<void*>(taskId), DWORD(flags));
            }
        }
        finally
        {
            service->Release();
            service = nullptr;
        }
    }
}
