//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

namespace AIMP.SDK
{
    /// <summary>
    /// Enum AimpPlayerState
    /// </summary>
    public enum AimpPlayerState
    {
        /// <summary>
        /// The stopped
        /// </summary>
        Stopped,

        /// <summary>
        /// The pause
        /// </summary>
        Pause,

        /// <summary>
        /// The playing
        /// </summary>
        Playing
    }

    /// <summary>
    /// Enum AimpWindowHandleTypes
    /// </summary>
    public enum AimpWindowHandleTypes
    {
        /// <summary>
        /// The main form
        /// </summary>
        MainForm = 0,

        /// <summary>
        /// The application
        /// </summary>
        Application = 1,

        /// <summary>
        /// The tray control
        /// </summary>
        TrayControl = 2,

        /// <summary>
        /// The playlist form
        /// </summary>
        PlaylistForm = 3,

        /// <summary>
        /// The equalizer form
        /// </summary>
        EqualizerForm = 4
    }
}
