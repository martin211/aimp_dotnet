/*
 * AIMP DotNet SDK
 *
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 */
 
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
