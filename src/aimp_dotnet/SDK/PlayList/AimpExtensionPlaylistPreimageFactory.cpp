// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpExtensionPlaylistPreimageFactory.h"
#include "AimpPlaylistPreimage.h"
#include "AimpPlaylistPreimageFolders.h"

AimpExtensionPlaylistPreimageFactory::
AimpExtensionPlaylistPreimageFactory(IAIMPExtensionPlaylistPreimageFactory* aimpObject) : AimpObject<
    IAIMPExtensionPlaylistPreimageFactory>(aimpObject) {
}

AimpActionResult<IAimpPlaylistPreimage^>^ AimpExtensionPlaylistPreimageFactory::CreatePreimage() {
    IAimpPlaylistPreimage^ preimage = nullptr;
    IAIMPPlaylistPreimage* image = nullptr;
    IAIMPPlaylistPreimageFolders* folders = nullptr;
    ActionResultType res = CheckResult(InternalAimpObject->CreatePreimage(&image));
    if (res == ActionResultType::OK && image != nullptr) {
        if (image->QueryInterface(IID_IAIMPPlaylistPreimageFolders, reinterpret_cast<void**>(&folders)) == S_OK) {
            preimage = gcnew AimpPlaylistPreimageFolders(folders);
        }
        else {
            preimage = gcnew AimpPlaylistPreimage(image);
        }
    }

    return gcnew AimpActionResult<IAimpPlaylistPreimage^>(res, preimage);
}

StringResult AimpExtensionPlaylistPreimageFactory::GetName() {
    String^ name = nullptr;
    IAIMPString* aimpString = nullptr;
    ActionResultType res = CheckResult(InternalAimpObject->GetName(&aimpString));
    if (res == ActionResultType::OK && aimpString != nullptr) {
        name = AimpConverter::ToManagedString(aimpString);
        aimpString->Release();
        aimpString = nullptr;
    }

    return STRING_RESULT(res, name);
}

StringResult AimpExtensionPlaylistPreimageFactory::GetId() {
    String^ id = nullptr;
    IAIMPString* aimpString = nullptr;
    ActionResultType res = CheckResult(InternalAimpObject->GetID(&aimpString));
    if (res == ActionResultType::OK && aimpString != nullptr) {
        id = AimpConverter::ToManagedString(aimpString);
        aimpString->Release();
        aimpString = nullptr;
    }

    return STRING_RESULT(res, id);
}

PreimageFactoryFlags AimpExtensionPlaylistPreimageFactory::GetFlags() {
    return static_cast<PreimageFactoryFlags>(InternalAimpObject->GetFlags());
}
