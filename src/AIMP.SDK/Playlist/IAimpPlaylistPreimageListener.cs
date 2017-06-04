// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

namespace AIMP.SDK.Playlist
{
    /// <summary>
    /// 
    /// </summary>
    /// <param name="sender">The sender.</param>
    public delegate void AimpPlaylistPreimageListenerHandler();

    /// <summary>
    /// The interface provides an ability to notify playlist about the changes in preimage.
    /// </summary>
    public interface IAimpPlaylistPreimageListener
    {
        /// <summary>
        /// Occurs when data changed.
        /// </summary>
        event AimpPlaylistPreimageListenerHandler DataChanged;

        /// <summary>
        /// Occurs when settings changed.
        /// </summary>
        event AimpPlaylistPreimageListenerHandler SettingsChanged;
    }
}