// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "Win32Manager.h"

using namespace System;

void AIMP::Win32::Win32Manager::SetParentWindow(IntPtr child, IntPtr parent)
{
    SetParent((HWND)child.ToPointer(), (HWND)parent.ToPointer());
}

System::Drawing::Point AIMP::Win32::Win32Manager::GetWindowPosition(IntPtr handle)
{
    RECT rc;
    HWND hndl = FindWindow("TAIMPMainForm", 0);

    if (GetWindowRect(hndl, &rc))
    {
        return System::Drawing::Point(rc.left, rc.top);
    }

    return System::Drawing::Point::Empty;
}

System::IntPtr AIMP::Win32::Win32Manager::GetAimpHandle()
{
    HWND hndl = FindWindow("TAIMPMainForm", 0);
    return IntPtr(hndl);
}
