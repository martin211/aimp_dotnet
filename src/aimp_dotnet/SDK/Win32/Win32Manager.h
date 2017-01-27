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
 
#include <windows.h>


namespace AIMP
{
    namespace Win32
    {
        using namespace System;

        using namespace AIMP::SDK::Win32;

        public ref class Win32Manager : public IWin32Manager
        {
        public:
            virtual void SetParentWindow(IntPtr child, IntPtr parent);

            virtual System::Drawing::Point GetWindowPosition(IntPtr handle);

            virtual IntPtr GetAimpHandle();
        };
    }
}
