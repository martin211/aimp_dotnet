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
            IAIMPString *str = NULL;
            try
            {
                str = AimpConverter::ToAimpString(keyPath);
                return CheckResult(InternalAimpObject->Delete(str));
            }
            finally
            {
                if (str != NULL)
                {
                    str->Release();
                    str = NULL;
                }
            }
        }

        float AimpConfig::GetValueAsFloat(String ^keyPath)
        {
            IAIMPString *str = NULL;
            try
            {
                str = AimpConverter::ToAimpString(keyPath);
                double val = 0;
                InternalAimpObject->GetValueAsFloat(str, &val);
                return val;
            }
            finally
            {
                if (str != NULL)
                {
                    str->Release();
                    str = NULL;
                }
            }
        }

        int AimpConfig::GetValueAsInt32(String ^keyPath)
        {
            IAIMPString *str = NULL;
            try
            {
                str = AimpConverter::ToAimpString(keyPath);
                int val;
                InternalAimpObject->GetValueAsInt32(str, &val);
                return val;
            }
            finally
            {
                if (str != NULL)
                {
                    str->Release();
                    str = NULL;
                }
            }
        }

        Int64 AimpConfig::GetValueAsInt64(String ^keyPath)
        {
            IAIMPString *str = NULL;
            try
            {
                str = AimpConverter::ToAimpString(keyPath);
                Int64 val;
                InternalAimpObject->GetValueAsInt64(str, &val);
                return val;
            }
            finally
            {
                if (str != NULL)
                {
                    str->Release();
                    str = NULL;
                }
            }
        }

        IAimpStream ^AimpConfig::GetValueAsStream(String ^keyPath)
        {
            IAIMPString *str = NULL;
            IAIMPStream *stream = NULL;
            try
            {
                str = AimpConverter::ToAimpString(keyPath);
                if (CheckResult(InternalAimpObject->GetValueAsStream(str, &stream)) == AimpActionResult::Ok && stream != NULL)
                {
                    return gcnew AimpStream(stream);
                }

                return nullptr;
            }
            finally
            {
                if (str != NULL)
                {
                    str->Release();
                    str = NULL;
                }
            }
        }

        String ^AimpConfig::GetValueAsString(String ^keyPath)
        {
            IAIMPString *str = NULL;
            try
            {
                str = AimpConverter::ToAimpString(keyPath);
                IAIMPString* val = NULL;
                InternalAimpObject->GetValueAsString(str, &val);
                return val != NULL ? gcnew String(val->GetData()) : String::Empty;
            }
            finally
            {
                if (str != NULL)
                {
                    str->Release();
                    str = NULL;
                }
            }
        }

        AimpActionResult AimpConfig::SetValueAsFloat(String ^keyPath, float value)
        {
            IAIMPString *str = NULL;
            try
            {
                str = AimpConverter::ToAimpString(keyPath);
                return CheckResult(InternalAimpObject->SetValueAsFloat(str, value));
            }
            finally
            {
                if (str != NULL)
                {
                    str->Release();
                    str = NULL;
                }
            }
        }

        AimpActionResult AimpConfig::SetValueAsInt32(String ^keyPath, int value)
        {
            IAIMPString *str = NULL;
            try
            {
                str = AimpConverter::ToAimpString(keyPath);
                return CheckResult(InternalAimpObject->SetValueAsInt32(str, value));
            }
            finally
            {
                if (str != NULL)
                {
                    str->Release();
                    str = NULL;
                }
            }
        }

        AimpActionResult AimpConfig::SetValueAsInt64(String ^keyPath, Int64 value)
        {
            IAIMPString *str = NULL;
            try
            {
                str = AimpConverter::ToAimpString(keyPath);
                return CheckResult(InternalAimpObject->SetValueAsInt64(str, value));
            }
            finally
            {
                if (str != NULL)
                {
                    str->Release();
                    str = NULL;
                }
            }
        }

        AimpActionResult AimpConfig::SetValueAsStream(String ^keyPath, IAimpStream ^stream)
        {
            IAIMPString *str = NULL;
            try
            {
                str = AimpConverter::ToAimpString(keyPath);
                return CheckResult(InternalAimpObject->SetValueAsStream(str, ((AimpStream^)stream)->InternalAimpObject));
            }
            finally
            {
                if (str != NULL)
                {
                    str->Release();
                    str = NULL;
                }
            }
        }

        AimpActionResult AimpConfig::SetValueAsString(String ^keyPath, String ^value)
        {
            IAIMPString *str = NULL;
            IAIMPString *val = NULL;
            try
            {
                str = AimpConverter::ToAimpString(keyPath);
                val = AimpConverter::ToAimpString(value);
                return CheckResult(InternalAimpObject->SetValueAsString(str, val));
            }
            finally
            {
                if (str != NULL)
                {
                    str->Release();
                    str = NULL;
                }

                if (val != NULL)
                {
                    val->Release();
                    val = NULL;
                }
            }
        }
    }
}
