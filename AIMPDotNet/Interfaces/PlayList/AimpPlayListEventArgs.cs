namespace AIMP.SDK.Services.PlayList
{
    using System;

    public class AimpPlayListEventArgs : EventArgs
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="AimpPlayListEventArgs"/> class.
        /// </summary>
        /// <param name="playlist">The playlist.</param>
        public AimpPlayListEventArgs(IAimpPlayList playlist)
        {
            Playlist = playlist;
        }

        /// <summary>
        /// Gets the playlist.
        /// </summary>
        public IAimpPlayList Playlist { get; private set; }
    }
}