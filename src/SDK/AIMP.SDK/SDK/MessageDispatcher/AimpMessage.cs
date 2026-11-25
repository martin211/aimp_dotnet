using System;

namespace AIMP.SDK.MessageDispatcher;

[Flags]
public enum AimpMessage
{
    EndOfQueue = 1,
    EndOfPlaylist = 2,
    HasNextTrack = 4
}