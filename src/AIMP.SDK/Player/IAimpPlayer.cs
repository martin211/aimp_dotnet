// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using System;
using AIMP.SDK.ActionManager;
using AIMP.SDK.AlbumArtManager;
using AIMP.SDK.ConfigurationManager;
using AIMP.SDK.MenuManager;
using AIMP.SDK.MUIManager;
using AIMP.SDK.Options;
using AIMP.SDK.Playback;
using AIMP.SDK.Win32;
using AIMP.SDK.FileManager;
using AIMP.SDK.Lyrics;
using AIMP.SDK.MessageDispatcher;
using AIMP.SDK.MusicLibrary;
using AIMP.SDK.Playlist;
using AIMP.SDK.TagEditor;
using AIMP.SDK.Threading;

namespace AIMP.SDK.Player
{
    /// <summary>
    /// Interface IAimpPlayer
    /// Implements the <see cref="System.IDisposable" />
    /// </summary>
    /// <seealso cref="System.IDisposable" />
    public interface IAimpPlayer : IDisposable
    {
        /// <summary>
        /// Gets Player core.
        /// </summary>
        /// <value>The core.</value>
        IAimpCore Core { get; }

        /// <summary>
        /// Gets player menu manager.
        /// </summary>
        /// <value>The menu manager.</value>
        IAimpServiceMenuManager MenuManager { get; }

        /// <summary>
        /// Gets player action manager.
        /// </summary>
        /// <value>The action manager.</value>
        IAimpServiceActionManager ActionManager { get; }

        /// <summary>
        /// Gets the MUI manager.
        /// </summary>
        /// <value>The MUI manager.</value>
        // ReSharper disable InconsistentNaming
        IAimpMUIManager MUIManager { get; }
        // ReSharper restore InconsistentNaming

        /// <summary>
        /// Gets the album art manager.
        /// </summary>
        /// <value>The service album art.</value>
        IAimpServiceAlbumArt ServiceAlbumArt { get; }

        /// <summary>
        /// Gets the service album art cache.
        /// </summary>
        /// <value>The service album art cache.</value>
        IAimpServiceAlbumArtCache ServiceAlbumArtCache { get; }

        /// <summary>
        /// Gets the configuration manager.
        /// </summary>
        /// <value>The service configuration.</value>
        IAimpServiceConfig ServiceConfig { get; }

        /// <summary>
        /// Gets the play list manager.
        /// </summary>
        /// <value>The playlist manager.</value>
        IAimpPlaylistManager2 PlaylistManager { get; }

        /// <summary>
        /// Gets the playback queue manager.
        /// </summary>
        /// <value>The service playback queue.</value>
        IAimpServicePlaybackQueue ServicePlaybackQueue { get; }

        /// <summary>
        /// Gets the service options dialog.
        /// </summary>
        /// <value>The service options dialog.</value>
        IAimpServiceOptionsDialog ServiceOptionsDialog { get; }

        /// <summary>
        /// Gets the service message dispatcher.
        /// </summary>
        /// <value>The service message dispatcher.</value>
        IAimpServiceMessageDispatcher ServiceMessageDispatcher { get; }

        /// <summary>
        /// Gets or sets a value indicating whether the volume is mute.
        /// </summary>
        /// <value><c>true</c> if this instance is mute; otherwise, <c>false</c>.</value>
        bool IsMute { get; set; }

        /// <summary>
        /// Gets or sets the volume.
        /// </summary>
        /// <value>The volume.</value>
        float Volume { get; set; }

        /// <summary>
        /// Gets the duration.
        /// </summary>
        /// <value>The duration.</value>
        double Duration { get; }

        /// <summary>
        /// Gets or sets the position.
        /// </summary>
        /// <value>The position.</value>
        double Position { get; set; }

        /// <summary>
        /// Gets the current player state <see cref="AimpPlayerState" />.
        /// </summary>
        /// <value>The state.</value>
        AimpPlayerState State { get; }

        /// <summary>
        /// Gets the current playing file.
        /// </summary>
        /// <value>The current file information.</value>
        IAimpFileInfo CurrentFileInfo { get; }

        /// <summary>
        /// Gets the current play list item.
        /// </summary>
        /// <value>The current play list item.</value>
        IAimpPlaylistItem CurrentPlaylistItem { get; }

        /// <summary>
        /// Gets the win32 manager.
        /// </summary>
        /// <value>The win32 manager.</value>
        IWin32Manager Win32Manager { get; }

        /// <summary>
        /// Gets the service synchronizer.
        /// </summary>
        /// <value>The service synchronizer.</value>
        IAimpServiceSynchronizer ServiceSynchronizer { get; }

        /// <summary>
        /// Gets the service thread pool.
        /// </summary>
        /// <value>The service thread pool.</value>
        IAimpServiceThreadPool ServiceThreadPool { get; }

        /// <summary>
        /// Gets the service music library.
        /// </summary>
        /// <value>The service music library.</value>
        IAimpServiceMusicLibrary ServiceMusicLibrary { get; }

        /// <summary>
        /// Gets the service music library UI.
        /// </summary>
        /// <value>The service music library UI.</value>
        IAimpServiceMusicLibraryUI ServiceMusicLibraryUi { get; }

        /// <summary>
        /// Gets the service file formats.
        /// </summary>
        /// <value>The service file formats.</value>
        IAimpServiceFileFormats ServiceFileFormats { get; }

        /// <summary>
        /// Gets the service file information.
        /// </summary>
        /// <value>The service file information.</value>
        IAimpServiceFileInfo ServiceFileInfo { get; }

        /// <summary>
        /// Gets the service file systems.
        /// </summary>
        /// <value>The service file systems.</value>
        IAimpServiceFileSystems ServiceFileSystems { get; }

        /// <summary>
        /// Gets the service file streaming.
        /// </summary>
        /// <value>The service file streaming.</value>
        IAimpServiceFileStreaming ServiceFileStreaming { get; }

        /// <summary>
        /// Gets the file information formatter service.
        /// </summary>
        /// <value>The service file information formatter.</value>
        IAimpServiceFileInfoFormatter ServiceFileInfoFormatter { get; }

        /// <summary>
        /// Gets the service file tag editor.
        /// </summary>
        /// <value>The service file tag editor.</value>
        IAimpServiceFileTagEditor ServiceFileTagEditor { get; }

        /// <summary>
        /// Gets the service lyrics.
        /// </summary>
        /// <value>The service lyrics.</value>
        IAimpServiceLyrics ServiceLyrics { get; }

        /// <summary>
        /// Pauses player.
        /// </summary>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Pause();

        /// <summary>
        /// Resumes player.
        /// </summary>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Resume();

        /// <summary>
        /// Stops player.
        /// </summary>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Stop();

        /// <summary>
        /// Stops the after track.
        /// </summary>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult StopAfterTrack();

        /// <summary>
        /// Goes to next track.
        /// </summary>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult GoToNext();

        /// <summary>
        /// Goes to previous track.
        /// </summary>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult GoToPrev();

        /// <summary>
        /// Plays the specified queue item.
        /// </summary>
        /// <param name="queueItem">The queue item.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Play(IAimpPlaybackQueueItem queueItem);

        /// <summary>
        /// Plays the specified play list item.
        /// </summary>
        /// <param name="playlistItem">The play list item.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Play(IAimpPlaylistItem playlistItem);

        /// <summary>
        /// Plays the specified play list.
        /// </summary>
        /// <param name="playList">The play list.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Play(IAimpPlaylist playList);
    }
}