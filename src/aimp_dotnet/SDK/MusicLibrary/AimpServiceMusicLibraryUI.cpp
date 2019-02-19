// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpServiceMusicLibraryUI.h"

using namespace AIMP::SDK;

AimpServiceMusicLibraryUI::AimpServiceMusicLibraryUI(ManagedAimpCore^ core) : AimpBaseManager<IAIMPServiceMusicLibraryUI>(core)
{

}

AimpActionResult AimpServiceMusicLibraryUI::GetFiles(FilesType flags, IAimpFileList^% list)
{
    list = nullptr;
    IAIMPServiceMusicLibraryUI* service = nullptr;
    AimpActionResult result = AimpActionResult::Fail;

    try
    {
        result = GetService(IID_IAIMPServiceMusicLibraryUI, &service);
        if (result == AimpActionResult::OK && service != nullptr)
        {
            IAIMPMLFileList* l = nullptr;
            result = CheckResult(service->GetFiles(int(flags), l));

            if (result == AimpActionResult::OK && l != nullptr)
            {
                list = gcnew AimpFileList(l);
            }
        }
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }
    }

    return result;
}

AimpActionResult AimpServiceMusicLibraryUI::GetGroupingFilter(IAimpDataFilter^% filter)
{
    filter = nullptr;
    AimpActionResult result = AimpActionResult::Fail;
    IAIMPServiceMusicLibraryUI* service = nullptr;

    try
    {
        result = GetService(IID_IAIMPServiceMusicLibraryUI, &service);
        if (result == AimpActionResult::OK && service != nullptr)
        {
            IAIMPMLDataFilter* f = nullptr;
            result = CheckResult(service->GetGroupingFilter(&f));

            if (result == AimpActionResult::OK && f != nullptr)
            {
                filter = gcnew AimpDataFilter(f);
            }
        }
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }
    }

    return result;
}

AimpActionResult AimpServiceMusicLibraryUI::GetGroupingFilterPath(String^% path)
{
    path = String::Empty;
    IAIMPServiceMusicLibraryUI* service = nullptr;
    AimpActionResult result = AimpActionResult::Fail;

    try
    {
        result = GetService(IID_IAIMPServiceMusicLibraryUI, &service);
        if (result == AimpActionResult::OK && service != nullptr)
        {
            IAIMPString* str = nullptr;
            result = CheckResult(service->GetGroupingFilterPath(&str));

            if (result == AimpActionResult::OK && str != nullptr)
            {
                path = AimpConverter::ToManagedString(str);
            }
        }
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }
    }

    return result;
}

AimpActionResult AimpServiceMusicLibraryUI::SetGroupingFilterPath(String^ path)
{
    IAIMPServiceMusicLibraryUI* service = nullptr;
    AimpActionResult result = AimpActionResult::Fail;
    IAIMPString* strPath = nullptr;

    try
    {
        result = GetService(IID_IAIMPServiceMusicLibraryUI, &service);
        if (result == AimpActionResult::OK && service != nullptr)
        {
            strPath = AimpConverter::ToAimpString(path);
            result = CheckResult(service->SetGroupingFilterPath(strPath));
        }
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }

        if (strPath != nullptr)
        {
            strPath->Release();
            strPath = nullptr;
        }
    }

    return result;
}
