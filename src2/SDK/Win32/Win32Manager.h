/*
 * AIMP DotNet SDK
 *
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
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
