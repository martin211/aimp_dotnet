using System;
using AIMP.SDK.PlayList.Objects;

namespace AIMP.SDK.PlayList;

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