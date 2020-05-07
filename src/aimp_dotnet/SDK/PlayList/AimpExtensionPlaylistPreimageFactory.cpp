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
#include "AimpExtensionPlaylistPreimageFactory.h"
#include "AimpPlaylistPreimage.h"
#include "AimpPlaylistPreimageFolders.h"

AimpExtensionPlaylistPreimageFactory::
AimpExtensionPlaylistPreimageFactory(IAIMPExtensionPlaylistPreimageFactory* aimpObject) : AimpObject<
    IAIMPExtensionPlaylistPreimageFactory>(aimpObject)
{
}

ActionResultType AimpExtensionPlaylistPreimageFactory::CreatePreimage(IAimpPlaylistPreimage^% preimage)
{
    IAIMPPlaylistPreimage* image = nullptr;
    IAIMPPlaylistPreimageFolders* folders = nullptr;
    ActionResultType res = CheckResult(InternalAimpObject->CreatePreimage(&image));
    if (res == ActionResultType::OK && image != nullptr)
    {
        if (image->QueryInterface(IID_IAIMPPlaylistPreimageFolders, reinterpret_cast<void**>(&folders)) == S_OK)
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

ActionResultType AimpExtensionPlaylistPreimageFactory::GetName(String^% name)
{
    IAIMPString* aimpString = nullptr;
    ActionResultType res = CheckResult(InternalAimpObject->GetName(&aimpString));
    if (res == ActionResultType::OK && aimpString != nullptr)
    {
        name = AimpConverter::ToManagedString(aimpString);
        aimpString->Release();
        aimpString = nullptr;
    }

    return res;
}

ActionResultType AimpExtensionPlaylistPreimageFactory::GetId(String^% id)
{
    IAIMPString* aimpString = nullptr;
    ActionResultType res = CheckResult(InternalAimpObject->GetID(&aimpString));
    if (res == ActionResultType::OK && aimpString != nullptr)
    {
        id = AimpConverter::ToManagedString(aimpString);
        aimpString->Release();
        aimpString = nullptr;
    }

    return res;
}

PreimageFactoryFlags AimpExtensionPlaylistPreimageFactory::GetFlags()
{
    return static_cast<PreimageFactoryFlags>(InternalAimpObject->GetFlags());
}
