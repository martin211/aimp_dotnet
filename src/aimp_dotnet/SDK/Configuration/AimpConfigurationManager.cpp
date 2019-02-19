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
#include "AimpConfigurationManager.h"

AimpServiceConfig::AimpServiceConfig(IAIMPServiceConfig* aimpObject) : AimpConfig(aimpObject)
{
}

AimpServiceConfig::~AimpServiceConfig()
{
}

AimpActionResult AimpServiceConfig::FlushCache()
{
    return CheckResult(static_cast<IAIMPServiceConfig*>(InternalAimpObject)->FlushCache());
}
