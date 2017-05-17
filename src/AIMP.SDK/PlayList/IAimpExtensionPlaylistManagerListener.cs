namespace AIMP.SDK.PlayList
{
    /// <summary>
    /// Delegate for playlist events.
    /// </summary>
    /// <param name="playListName">Name of the playlist.</param>
    /// <param name="playListId">The playlist identifier.</param>
    public delegate void PlayListHandler(string playlistName, string playlistId);

    /// <summary>
    /// This is extension for <see cref="IAimpPlayListManager"/> service, provides an ability to receive notifications about the changes in manager.
    /// </summary>
    public interface IAimpExtensionPlaylistManagerListener
    {
        /// <summary>
        /// Occurs when playlist activated.
        /// </summary>
        event PlayListHandler PlaylistActivated;

        /// <summary>
        /// Occurs when playlist added.
        /// </summary>
        event PlayListHandler PlaylistAdded;

        /// <summary>
        /// Occurs when playlist removed.
        /// </summary>
        event PlayListHandler PlaylistRemoved;
    }
}