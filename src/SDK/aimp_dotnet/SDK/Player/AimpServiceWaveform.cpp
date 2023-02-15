//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpServiceWaveform.h"

AimpServiceWaveform::AimpServiceWaveform(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceWaveform>(core) {
}

IAIMPServiceWaveform* AimpServiceWaveform::GetAimpService() {
    IAIMPServiceWaveform* service = nullptr;
    GetService(IID_IAIMPServiceWaveform, &service);
    return service;
}
