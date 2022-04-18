// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

namespace AIMP {
    namespace Win32 {
        using namespace System;

        using namespace Win32;

        public ref class Win32Manager : public IWin32Manager {
        public:
            virtual void SetParentWindow(IntPtr child, IntPtr parent);

            virtual Point GetWindowPosition(IntPtr handle);

            virtual IntPtr GetAimpHandle();
        };
    }
}
