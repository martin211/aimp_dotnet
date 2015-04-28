using System;

namespace AIMP.SDK.Services.PlayListManager
{
    public class PlayListEventArgs : EventArgs
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="PlayListEventArgs"/> class.
        /// </summary>
        /// <param name="playlist">The playlist.</param>
        public PlayListEventArgs(IAimpPlayList playlist)
        {
            Playlist = playlist;
        }

        /// <summary>
        /// Gets the playlist.
        /// </summary>
        public IAimpPlayList Playlist { get; private set; }
    }
}