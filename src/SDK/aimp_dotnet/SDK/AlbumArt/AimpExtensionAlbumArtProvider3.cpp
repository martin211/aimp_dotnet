//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "stdafx.h"
#include "AimpExtensionAlbumArtProvider3.h"

#include "AimpAlbumArtRequest.h"
#include "SDK/FileManager/AimpFileInfo.h"
#include "SDK/Objects/AimpImageContainer.h"

AimpExtensionAlbumArtProvider3::AimpExtensionAlbumArtProvider3(gcroot<IAimpExtensionAlbumArtProvider3^> managed) {
    _managed = managed;
}

HRESULT AimpExtensionAlbumArtProvider3::Get(IAIMPFileInfo* fileInfo, IAIMPAlbumArtRequest* request, IAIMPImageContainer** image) {
    IAimpFileInfo^ fi = gcnew AimpFileInfo(fileInfo);
    const auto r = _managed->Get(fi, gcnew AimpAlbumArtRequest(request));
    if (r->ResultType == ActionResultType::OK && r->Result != nullptr) {
        const auto container = safe_cast<AimpImageContainer^>(r->Result);
        if (container == nullptr) {
            return E_UNEXPECTED;
        }

        *image = container->InternalAimpObject;
        return S_OK;
    }

    return E_UNEXPECTED;
}

DWORD AimpExtensionAlbumArtProvider3::GetCategory() {
    return static_cast<DWORD>(_managed->GetCategory());
}
