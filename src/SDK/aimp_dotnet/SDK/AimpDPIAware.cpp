//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpDPIAware.h"

AimpDPIAware::AimpDPIAware(IAIMPDPIAware* obj) : AimpObject<IAIMPDPIAware>(obj) {
}

int AimpDPIAware::DPI::get() {
    return InternalAimpObject->GetDPI();
}

void AimpDPIAware::DPI::set(int dpi) {
    InternalAimpObject->SetDPI(dpi);
}
