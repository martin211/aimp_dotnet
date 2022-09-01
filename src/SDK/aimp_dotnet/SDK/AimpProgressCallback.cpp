//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "stdafx.h"
#include "AimpProgressCallback.h"

AimpProgressCallback::AimpProgressCallback(IAIMPProgressCallback* aimpObject)
    : AimpObject<IAIMPProgressCallback>(aimpObject) {
}

AimpActionResult^ AimpProgressCallback::Process(double progress, bool canceled) {
    InternalAimpObject->Process(progress, &canceled);
    return gcnew AimpActionResult(ActionResultType::OK);
}
