#pragma once

#include "..\BaseManager.h"
#include "..\Converter.h"

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
                    service->Release();
                    str->Release();
                    str = NULL;
                    service = NULL;
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
                        service->GetValue(Converter::MakeAimpString(_core->GetAimpCore(), key), &str);
                        if (str == NULL)
                        {
                            return String::Empty;
                        }

                        return gcnew String(str->GetData());
                    }
                }
                finally
                {
                    service->Release();
                    str->Release();
                    str = NULL;
                    service = NULL;
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
                        service->GetValuePart(Converter::MakeAimpString(_core->GetAimpCore(), key), index, &str);

                        if (str == NULL)
                        {
                            return String::Empty;
                        }

                        return gcnew String(str->GetData());
                    }
                }
                finally
                {
                    service->Release();
                    str->Release();
                    str = NULL;
                    service = NULL;
                }

                return String::Empty;
            }
        };
    }
}