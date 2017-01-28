/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 * 
 */
#pragma once

#include "SDK\BaseManager.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK::MUIManager;

        public ref class AimpMIUManager : public AimpBaseManager<IAIMPServiceMUI>, public IAimpMUIManager
        {
        public:
            explicit AimpMIUManager(ManagedAimpCore^ core);

            ~AimpMIUManager();

            virtual String^ GetName();

            virtual String^ GetValue(String^ key);

            virtual String^ GetValuePart(String^ key, int index);
        };
    }
}
