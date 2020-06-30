// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpServiceMusicLibraryUI.h"

using namespace AIMP::SDK;

AimpServiceMusicLibraryUI::
AimpServiceMusicLibraryUI(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceMusicLibraryUI>(core)
{
}

ActionResultType AimpServiceMusicLibraryUI::GetFiles(FilesType flags, IAimpFileList^% list)
{
    list = nullptr;
    IAIMPServiceMusicLibraryUI* service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;

    try
    {
        if (service != nullptr)
        {
            IAIMPMLFileList* l = nullptr;
            result = CheckResult(service->GetFiles(int(flags), l));

            if (result == ActionResultType::OK && l != nullptr)
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

ActionResultType AimpServiceMusicLibraryUI::GetGroupingFilter(IAimpDataFilter^% filter)
{
    filter = nullptr;
    ActionResultType result = ActionResultType::Fail;
    IAIMPServiceMusicLibraryUI* service = GetAimpService();

    try
    {
        if (service != nullptr)
        {
            IAIMPMLDataFilter* f = nullptr;
            result = CheckResult(service->GetGroupingFilter(&f));

            if (result == ActionResultType::OK && f != nullptr)
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

ActionResultType AimpServiceMusicLibraryUI::GetGroupingFilterPath(String^% path)
{
    path = String::Empty;
    IAIMPServiceMusicLibraryUI* service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;

    try
    {
        if (service != nullptr)
        {
            IAIMPString* str = nullptr;
            result = CheckResult(service->GetGroupingFilterPath(&str));

            if (result == ActionResultType::OK && str != nullptr)
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

ActionResultType AimpServiceMusicLibraryUI::SetGroupingFilterPath(String^ path)
{
    IAIMPServiceMusicLibraryUI* service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;
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
