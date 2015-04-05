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
		};
	}
}