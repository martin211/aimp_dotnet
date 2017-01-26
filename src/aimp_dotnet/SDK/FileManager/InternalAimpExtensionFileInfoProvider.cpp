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
