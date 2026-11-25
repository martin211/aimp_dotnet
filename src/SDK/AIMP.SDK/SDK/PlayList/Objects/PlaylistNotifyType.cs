using System;

namespace AIMP.SDK.PlayList.Objects;

/// <summary>
/// Enum PlaylistNotifyType
/// </summary>
[Flags]
public enum PlaylistNotifyType
{
    /// <summary>
    /// Play list name has been changed.
    /// </summary>
    AIMP_PLAYLIST_NOTIFY_NAME = 1,

    /// <summary>
    /// Selected items has been changed.
    /// </summary>
    AIMP_PLAYLIST_NOTIFY_SELECTION = 2,

    /// <summary>
    /// Playback focus has been changed.
    /// </summary>
    AIMP_PLAYLIST_NOTIFY_PLAYBACKCURSOR = 4,

    /// <summary>
    /// Read only flag has been changed.
    /// </summary>
    AIMP_PLAYLIST_NOTIFY_READONLY = 8,

    /// <summary>
    /// Record focus has been changed.
    /// </summary>
    AIMP_PLAYLIST_NOTIFY_FOCUSINDEX = 16,

    /// <summary>
    /// Changed records order.
    /// </summary>
    AIMP_PLAYLIST_NOTIFY_CONTENT = 32,

    /// <summary>
    /// Information about one or more files has been changed.
    /// </summary>
    AIMP_PLAYLIST_NOTIFY_FILEINFO = 64,

    /// <summary>
    /// Statistic for one or more files has been changed.
    /// </summary>
    AIMP_PLAYLIST_NOTIFY_STATISTICS = 128,

    /// <summary>
    /// Changed auto play switch.
    /// </summary>
    AIMP_PLAYLIST_NOTIFY_PLAYINGSWITCHS = 256,

    /// <summary>
    /// Path to pre image has been changed.
    /// </summary>
    AIMP_PLAYLIST_NOTIFY_PREIMAGE = 512,

    /// <summary>
    /// Playlist has been modified.
    /// </summary>
    AIMP_PLAYLIST_NOTIFY_MODIFIED = 1024,

    /// <summary>
    /// Dead state of items has been changed.
    /// </summary>
    AIMP_PLAYLIST_NOTIFY_DEADSTATE = 2048,

    /// <summary>
    /// Make visible request.
    /// </summary>
    AIMP_PLAYLIST_NOTIFY_MAKEVISIBLE = 4096,

    /// <summary>
    /// Playback queue has been changed.
    /// </summary>
    AIMP_PLAYLIST_NOTIFY_PLAYBACKQUEUE = 8192,

    /// <summary>
    /// Playback bookmark has been changed (AIMP 5.40+).
    /// </summary>
    AIMP_PLAYLIST_NOTIFY_PLAYBACKBOOKMARK = 16384,

    /// <summary>
    /// Group name has been changed (AIMP 5.40+).
    /// </summary>
    AIMP_PLAYLIST_NOTIFY_GROUPNAME = 32768,

    /// <summary>
    /// Playlist settings has been changed (AIMP 6.0+).
    /// </summary>
    AIMP_PLAYLIST_NOTIFY_SETTINGS = 65536
}