//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;
using AIMP.SDK.Playlist.Objects;

namespace AIMP.SDK.Playlist
{
    /// <summary>
    /// Class AimpPlaylistEventArgs.
    /// Implements the <see cref="System.EventArgs" />
    /// </summary>
    /// <seealso cref="System.EventArgs" />
    public class AimpPlaylistEventArgs : EventArgs
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="AimpPlaylistEventArgs" /> class.
        /// </summary>
        /// <param name="playlist">The playlist.</param>
        public AimpPlaylistEventArgs(IAimpPlaylist playlist)
        {
            Playlist = playlist;
        }

        /// <summary>
        /// Gets the playlist.
        /// </summary>
        /// <value>The playlist.</value>
        public IAimpPlaylist Playlist { get; }
    }
}
