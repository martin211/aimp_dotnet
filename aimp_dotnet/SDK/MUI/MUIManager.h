#pragma once

#include "..\BaseManager.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK::MUIManager;

        public ref class AimpMIUManager : public AimpBaseManager<IAIMPServiceMUI>, public IAimpMUIManager
        {
        public:
            explicit AimpMIUManager(ManagedAimpCore^ core) : AimpBaseManager<IAIMPServiceMUI>(core)
            {
                
            }

            ~AimpMIUManager()
            {
                System::Diagnostics::Debug::WriteLine("Dispose AimpMIUManager");
            }

            virtual String^ GetName()
            {
                IAIMPString *str = NULL;
                IAIMPServiceMUI* service = NULL;
                try
                {
                    if (GetService(IID_IAIMPServiceMUI, &service) == AimpActionResult::Ok)
                    {
                        service->GetName(&str);
                        return gcnew String(str->GetData());
                    }
                }
                finally
                {
                    if (service != NULL)
                    {
                        service->Release();
                        service = NULL;
                    }

                    if (str != NULL)
                    {
                        str->Release();
                        str = NULL;
                    }
                }

                return String::Empty;
            }

            virtual String^ GetValue(String^ key)
            {
                IAIMPString *str = NULL;
                IAIMPServiceMUI* service = NULL;
                try
                {
                    if (GetService(IID_IAIMPServiceMUI, &service) == AimpActionResult::Ok)
                    {
                        IAIMPString* strKey = AimpConverter::GetAimpString(key);

                        if (service->GetValue(strKey, &str) == S_OK)
                        {
                            strKey->Release();

                            if (str == NULL)
                            {
                                return String::Empty;
                            }

                            return gcnew String(str->GetData());
                        }
                    }
                }
                finally
                {
                    if (service != NULL)
                    {
                        service->Release();
                        service = NULL;
                    }

                    if (str != NULL)
                    {
                        str->Release();
                        str = NULL;
                    }
                }

                return String::Empty;
            }

            virtual String^ GetValuePart(String^ key, int index)
            {
                IAIMPString *str = NULL;
                IAIMPServiceMUI* service = NULL;
                try
                {
                    if (GetService(IID_IAIMPServiceMUI, &service) == AimpActionResult::Ok)
                    {
                        IAIMPString* strKey = AimpConverter::GetAimpString(key);
                        service->GetValuePart(strKey, index, &str);

                        strKey->Release();

                        if (str == NULL)
                        {
                            return String::Empty;
                        }

                        return gcnew String(str->GetData());
                    }
                }
                finally
                {
                    if (service != NULL)
                    {
                        service->Release();
                        service = NULL;
                    }

                    if (str != NULL)
                    {
                        str->Release();
                        str = NULL;
                    }
                }

                return String::Empty;
            }
        };
    }
}