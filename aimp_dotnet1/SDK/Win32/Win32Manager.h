#include <windows.h>


namespace AIMP
{
	namespace Win32
	{
		using namespace System;

		using namespace AIMP::SDK::Services::Win32Manager;

		public ref class Win32Manager : public IWin32Manager
		{
		public:
			virtual void SetParentWindow(IntPtr child, IntPtr parent)
			{
				SetParent((HWND)child.ToPointer(), (HWND)parent.ToPointer());
			}

			virtual System::Drawing::Point GetWindowPosition(IntPtr handle)
			{
				RECT rc;
				HWND hndl = FindWindow(L"TAIMPMainForm", 0);
				
				if (GetWindowRect(hndl, &rc))
				{
					return System::Drawing::Point(rc.left, rc.top);
				}
			}

			virtual IntPtr GetAimpHandle()
			{
				HWND hndl = FindWindow(L"TAIMPMainForm", 0);
				return IntPtr(hndl);
			}
		};
	}
}