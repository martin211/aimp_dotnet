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
#include "InternalAimpExtensionFileInfoProvider.h"
#include "AimpFileInfo.h"
#include "../../SDK/AimpString.h"

HRESULT WINAPI InternalAimpExtensionFileInfoProvider::GetFileInfo(IAIMPString* fileURI, IAIMPFileInfo* info)
{
    IAimpFileInfo^ aimpFileInfo = gcnew AimpFileInfo(info);
    IAimpString^ str = gcnew AimpString(fileURI);
    AimpActionResult result = _managedInstance->GetFileInfo(str, aimpFileInfo);
    info = static_cast<AimpFileInfo^>(aimpFileInfo)->InternalAimpObject;

    return HRESULT(result);
}

HRESULT WINAPI InternalAimpExtensionFileInfoProvider::GetFileInfo(IAIMPStream* stream, IAIMPFileInfo* info)
{
    // TODO: Complete it
    IAimpFileInfo^ aimpFileInfo = gcnew AimpFileInfo(info);
    //return (HRESULT)_managedInstance->GetFileInfo(null, aimpFileInfo);
    return E_NOTIMPL;
}
