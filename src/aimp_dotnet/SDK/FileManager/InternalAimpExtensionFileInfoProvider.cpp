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
#include "InternalAimpExtensionFileInfoProvider.h"
#include "AimpFileInfo.h"

HRESULT WINAPI InternalAimpExtensionFileInfoProvider::GetFileInfo(IAIMPString *FileURI, IAIMPFileInfo *Info)
{
    AIMP::SDK::FileManager::IAimpFileInfo^ aimpFileInfo = gcnew AimpFileInfo(Info);
    return (HRESULT)_managedInstance->GetFileInfo(AIMP::SDK::AimpConverter::ToManagedString(FileURI), aimpFileInfo);
}

HRESULT WINAPI InternalAimpExtensionFileInfoProvider::GetFileInfo(IAIMPStream *Stream, IAIMPFileInfo *Info)
{
    AIMP::SDK::FileManager::IAimpFileInfo^ aimpFileInfo = gcnew AimpFileInfo(Info);
    //return (HRESULT)_managedInstance->GetFileInfo(null, aimpFileInfo);
    return E_NOTIMPL;
}
