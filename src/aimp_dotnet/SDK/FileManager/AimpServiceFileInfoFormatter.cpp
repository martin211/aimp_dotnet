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
StringResult AimpServiceFileInfoFormatter::Format(String^ tmpl, IAimpFileInfo^ fileInfo)
{
    auto service = GetAimpService();
    IAIMPString* t = nullptr;
    ActionResultType res = ActionResultType::Fail;
    String^ formattedResult = nullptr;

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

    return gcnew AimpActionResult<String^>(res, formattedResult);
}

IAIMPServiceFileInfoFormatter* AimpServiceFileInfoFormatter::GetAimpService()
{
    IAIMPServiceFileInfoFormatter* service = nullptr;
    GetService(IID_IAIMPServiceFileInfoFormatter, &service);
    return service;
}


