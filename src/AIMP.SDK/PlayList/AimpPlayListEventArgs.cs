using System;

namespace AIMP.SDK.Playlist
{
    public class AimpPlaylistEventArgs : EventArgs
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="AimpPlaylistEventArgs"/> class.
        /// </summary>
        /// <param name="playlist">The playlist.</param>
        public AimpPlaylistEventArgs(IAimpPlaylist playlist)
        {
            Playlist = playlist;
        }

        /// <summary>
        /// Gets the playlist.
        /// </summary>
        public IAimpPlaylist Playlist { get; }
    }
}