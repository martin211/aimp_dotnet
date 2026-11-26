using System;

namespace AIMP.SDK.Core;

[Flags]
public enum ShutdownType : uint
{
    Hibernate = 0x1,
    PowerOff = 0x2,
    Sleep = 0x3,
    Reboot = 0x4,
    LogOff = 0x5,
    CloseApp = 0x10,
    NoConfirm = 0x20
}