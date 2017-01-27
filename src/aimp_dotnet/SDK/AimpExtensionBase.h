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
#include <windows.h>

namespace AIMP
{
    namespace SDK
    {
        using namespace System;

        public ref class AimpExtensionBase abstract
        {
        internal:
            property GUID ExtensionId
            {
                virtual GUID get() abstract;
            }

            property String ^Name
            {
                virtual String ^get() abstract;
            }

            property IUnknown *InternalProxyExtension
            {
                virtual IUnknown *get() abstract;
                virtual void set(IUnknown *value) abstract;
            }
        };
    }
}
