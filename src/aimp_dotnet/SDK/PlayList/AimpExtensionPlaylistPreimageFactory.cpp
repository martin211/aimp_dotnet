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
#include "AimpExtensionPlaylistPreimageFactory.h"
#include "AimpPlaylistPreimage.h"
#include "AimpPlaylistPreimageFolders.h"

AimpExtensionPlaylistPreimageFactory::AimpExtensionPlaylistPreimageFactory(IAIMPExtensionPlaylistPreimageFactory *aimpObject) : AimpObject<IAIMPExtensionPlaylistPreimageFactory>(aimpObject)
{ }

AimpActionResult AimpExtensionPlaylistPreimageFactory::CreatePreimage(IAimpPlaylistPreimage ^%preimage)
{
    IAIMPPlaylistPreimage* image = NULL;
    IAIMPPlaylistPreimageFolders* folders = NULL;
    AimpActionResult res = CheckResult(InternalAimpObject->CreatePreimage(&image));
    if (res == AimpActionResult::Ok && image != nullptr)
    {
        if (image->QueryInterface(IID_IAIMPPlaylistPreimageFolders, (void**)&folders) == S_OK)
        {
            preimage = gcnew AimpPlaylistPreimageFolders(folders);
        }
        else
        {
            preimage = gcnew AimpPlaylistPreimage(image);
        }
    }

    return res;
}

AimpActionResult AimpExtensionPlaylistPreimageFactory::GetName(String ^%name)
{
    IAIMPString *aimpString = NULL;
    AimpActionResult res = CheckResult(InternalAimpObject->GetName(&aimpString));
    if (res == AimpActionResult::Ok && aimpString != NULL)
    {
        name = AimpConverter::ToManagedString(aimpString);
        aimpString->Release();
        aimpString = NULL;
    }

    return res;
}

AimpActionResult AimpExtensionPlaylistPreimageFactory::GetId(String ^%id)
{
    IAIMPString *aimpString = NULL;
    AimpActionResult res = CheckResult(InternalAimpObject->GetID(&aimpString));
    if (res == AimpActionResult::Ok && aimpString != NULL)
    {
        id = AimpConverter::ToManagedString(aimpString);
        aimpString->Release();
        aimpString = NULL;
    }

    return res;
}

PreimageFactoryFlags AimpExtensionPlaylistPreimageFactory::GetFlags()
{
    return (PreimageFactoryFlags)InternalAimpObject->GetFlags();
}
