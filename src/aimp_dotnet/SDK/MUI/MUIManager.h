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
            explicit AimpMIUManager(ManagedAimpCore^ core);

            ~AimpMIUManager();

            virtual String^ GetName();

            virtual String^ GetValue(String^ key);

            virtual String^ GetValuePart(String^ key, int index);
        };
    }
}