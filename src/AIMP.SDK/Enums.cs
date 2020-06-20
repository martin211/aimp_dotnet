// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

namespace AIMP.SDK
{
    public enum AimpPlayerState
    {
        Stopped,

        Pause,

        Playing
    }

    public enum AimpWindowHandleTypes
    {
        MainForm = 0,
        Application = 1,
        TrayControl = 2,
        PlaylistForm = 3,
        EqualizerForm = 4
    }
}