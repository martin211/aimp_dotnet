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
