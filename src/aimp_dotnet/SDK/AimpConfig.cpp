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
#include "AimpConfig.h"

namespace AIMP
{
    namespace SDK
    {
        AimpConfig::AimpConfig(IAIMPConfig *aimpPlayList) : AimpObject(aimpPlayList)
        {
        }

        AimpActionResult AimpConfig::Delete(String ^keyPath)
        {
            
        }

        float AimpConfig::GetValueAsFloat(String ^keyPath)
        {

        }

        int AimpConfig::GetValueAsInt32(String ^keyPath)
        {

        }

        Int64 AimpConfig::GetValueAsInt64(String ^keyPath)
        {

        }

        IAimpStream ^AimpConfig::GetValueAsStream(String ^keyPath)
        {

        }

        String ^AimpConfig::GetValueAsString(String ^keyPath)
        {

        }

        AimpActionResult AimpConfig::SetValueAsFloat(float value)
        {

        }

        AimpActionResult AimpConfig::SetValueAsInt32(int value)
        {

        }

        AimpActionResult AimpConfig::SetValueAsInt64(Int64 value)
        {

        }

        AimpActionResult AimpConfig::SetValueAsStream(IAimpStream ^stream)
        {

        }

        AimpActionResult AimpConfig::SetValueAsString(String ^value)
        {

        }
    }
}
