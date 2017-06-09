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
    IAIMPServiceMusicLibraryUI* service = NULL;
    AimpActionResult result = AimpActionResult::Fail;

    try
    {
        result = GetService(IID_IAIMPServiceMusicLibraryUI, &service);
        if (result == AimpActionResult::Ok)
        {
            if (service != NULL)
            {
                IAIMPMLFileList *l = NULL;
                result = CheckResult(service->GetFiles((int)flags, l));

                if (result == AimpActionResult::Ok && l != NULL)
                {
                    list = gcnew AimpFileList(l);
                }
            }
        }
    }
    finally
    {
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }
    }

    return result;
}

AimpActionResult AimpServiceMusicLibraryUI::GetGroupingFilter(IAimpDataFilter^% filter)
{
    filter = nullptr;
    AimpActionResult result = AimpActionResult::Fail;
    IAIMPServiceMusicLibraryUI* service = NULL;

    try
    {
        result = GetService(IID_IAIMPServiceMusicLibraryUI, &service);
        if (result == AimpActionResult::Ok)
        {
            if (service != NULL)
            {
                IAIMPMLDataFilter *f = NULL;
                result = CheckResult(service->GetGroupingFilter(&f));

                if (result == AimpActionResult::Ok && f != NULL)
                {
                    filter = gcnew AimpDataFilter(f);
                }
            }
        }
    }
    finally
    {
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }
    }

    return result;
}

AimpActionResult AimpServiceMusicLibraryUI::GetGroupingFilterPath(String^% path)
{
    path = String::Empty;
    IAIMPServiceMusicLibraryUI* service = NULL;
    AimpActionResult result = AimpActionResult::Fail;

    try
    {
        result = GetService(IID_IAIMPServiceMusicLibraryUI, &service);
        if (result == AimpActionResult::Ok)
        {
            if (service != NULL)
            {
                IAIMPString *str = NULL;
                result = CheckResult(service->GetGroupingFilterPath(&str));

                if (result == AimpActionResult::Ok && str != NULL)
                {
                    path = AimpConverter::ToManagedString(str);
                }
            }
        }
    }
    finally
    {
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }
    }

    return result;
}

AimpActionResult AimpServiceMusicLibraryUI::SetGroupingFilterPath(String^ path)
{
    IAIMPServiceMusicLibraryUI* service = NULL;
    AimpActionResult result = AimpActionResult::Fail;
    IAIMPString* strPath = NULL;

    try
    {
        result = GetService(IID_IAIMPServiceMusicLibraryUI, &service);
        if (result == AimpActionResult::Ok)
        {
            if (service != NULL)
            {
                strPath = AimpConverter::ToAimpString(path);
                result = CheckResult(service->SetGroupingFilterPath(strPath));
            }
        }
    }
    finally
    {
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }

        if (strPath != NULL)
        {
            strPath->Release();
            strPath = NULL;
        }
    }

    return result;
}
