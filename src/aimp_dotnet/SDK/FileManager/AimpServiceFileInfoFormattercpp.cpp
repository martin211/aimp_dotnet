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
#include "AimpServiceFileInfoFormatter.h"
#include "AimpFileInfo.h"

AimpServiceFileInfoFormatter::AimpServiceFileInfoFormatter(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceFileInfoFormatter>(core)
{
    
}

/// <summary>
/// Formats the specified TMPL.
/// </summary>
/// <param name="tmpl">The TMPL.</param>
/// <param name="fileInfo">The file information.</param>
/// <param name="formattedResult">The formatted result.</param>
/// <returns>[Unknown].</returns>
ActionResultType AimpServiceFileInfoFormatter::Format(String^ tmpl, IAimpFileInfo^ fileInfo, String^% formattedResult)
{
    auto service = GetAimpService();
    IAIMPString* t = nullptr;
    ActionResultType res = ActionResultType::Fail;

    try
    {
        if (service != nullptr)
        {
            t = AimpConverter::ToAimpString(tmpl);
            auto fi = static_cast<AimpFileInfo^>(fileInfo)->InternalAimpObject;
            IAIMPString* result = nullptr;
            res = CheckResult(service->Format(t, fi, 0, nullptr, &result));
            if (res == ActionResultType::OK && result != nullptr)
            {
                formattedResult = AimpConverter::ToManagedString(result);
            }
        }
    }
    finally
    {
        ReleaseObject(service);
        ReleaseObject(t);
    }

    return res;
}

IAIMPServiceFileInfoFormatter* AimpServiceFileInfoFormatter::GetAimpService()
{
    IAIMPServiceFileInfoFormatter* service = nullptr;
    GetService(IID_IAIMPServiceFileInfoFormatter, &service);
    return service;
}


