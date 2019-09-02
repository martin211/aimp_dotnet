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
#include "AimpServiceMusicLibraryUI.h"

using namespace AIMP::SDK;

AimpServiceMusicLibraryUI::
AimpServiceMusicLibraryUI(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceMusicLibraryUI>(core)
{
}

AimpActionResult AimpServiceMusicLibraryUI::GetFiles(FilesType flags, IAimpFileList^% list)
{
    list = nullptr;
    IAIMPServiceMusicLibraryUI* service = GetAimpService();
    AimpActionResult result = AimpActionResult::Fail;

    try
    {
        if (service != nullptr)
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
        ReleaseObject(service);
    }

    return result;
}

AimpActionResult AimpServiceMusicLibraryUI::GetGroupingFilter(IAimpDataFilter^% filter)
{
    filter = nullptr;
    AimpActionResult result = AimpActionResult::Fail;
    IAIMPServiceMusicLibraryUI* service = GetAimpService();

    try
    {
        if (service != nullptr)
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
        ReleaseObject(service);
    }

    return result;
}

AimpActionResult AimpServiceMusicLibraryUI::GetGroupingFilterPath(String^% path)
{
    path = String::Empty;
    IAIMPServiceMusicLibraryUI* service = GetAimpService();
    AimpActionResult result = AimpActionResult::Fail;

    try
    {
        if (service != nullptr)
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
        ReleaseObject(service);
    }

    return result;
}

AimpActionResult AimpServiceMusicLibraryUI::SetGroupingFilterPath(String^ path)
{
    IAIMPServiceMusicLibraryUI* service = GetAimpService();
    AimpActionResult result = AimpActionResult::Fail;
    IAIMPString* strPath = nullptr;

    try
    {
        if (service != nullptr)
        {
            strPath = AimpConverter::ToAimpString(path);
            result = CheckResult(service->SetGroupingFilterPath(strPath));
        }
    }
    finally
    {
        ReleaseObject(service);
        ReleaseObject(strPath);
    }

    return result;
}

IAIMPServiceMusicLibraryUI* AimpServiceMusicLibraryUI::GetAimpService()
{
    IAIMPServiceMusicLibraryUI* service = nullptr;
    GetService(IID_IAIMPServiceMusicLibraryUI, &service);
    return service;
}
