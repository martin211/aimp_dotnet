/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
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
