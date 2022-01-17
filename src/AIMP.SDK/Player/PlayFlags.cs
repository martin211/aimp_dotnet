namespace AIMP.SDK.Player
{
    public enum PlayFlags
    {
        /// <summary>
        /// Player will search file with this file name in all loaded playlists, if succeeded - will start play it.
        /// </summary>
        FromPlaylist = 1,

        /// <summary>
        /// This flag should be used with previous one, if file is not found in loaded playlists - it will be added to playlist (target playlist is chosen based on current settings).
        /// </summary>
        CanAdd = 2,

        /// <summary>
        /// Start file playback without adding it to playlist.
        /// </summary>
        WithoutAdding = 4,

        /// <summary>
        /// Pause playback on track beginning.
        /// </summary>
        Suspend = 8
    }
}