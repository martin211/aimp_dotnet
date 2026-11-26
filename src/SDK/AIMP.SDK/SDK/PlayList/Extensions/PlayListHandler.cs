namespace AIMP.SDK.PlayList.Extensions;

/// <summary>
/// Delegate for playlist events.
/// </summary>
/// <param name="playlistName">Name of the playlist.</param>
/// <param name="playlistId">The playlist identifier.</param>
public delegate void PlayListHandler(string playlistName, string playlistId);