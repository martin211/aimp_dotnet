// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
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
    /// </summary>
    public interface IAimpPlayer : IDisposable
    {
        /// <summary>
        /// Gets Player core.
        /// </summary>
        IAimpCore Core { get; }

        /// <summary>
        /// Gets player menu manager.
        /// </summary>
        IAimpServiceMenuManager MenuManager { get; }

        /// <summary>
        /// Gets player action manager.
        /// </summary>
        IAimpServiceActionManager ActionManager { get; }

        /// <summary>
        /// Gets the MUI manager.
        /// </summary>
        // ReSharper disable InconsistentNaming
        IAimpMUIManager MUIManager { get; }
        // ReSharper restore InconsistentNaming

        /// <summary>
        /// Gets the album art manager.
        /// </summary>
        IAimpServiceAlbumArt ServiceAlbumArt { get; }

        IAimpServiceAlbumArtCache ServiceAlbumArtCache { get; }

        /// <summary>
        /// Gets the configuration manager.
        /// </summary>
        IAimpServiceConfig ServiceConfig { get; }

        /// <summary>
        /// Gets the play list manager.
        /// </summary>
        IAimpPlaylistManager2 PlaylistManager { get; }

        /// <summary>
        /// Gets the playback queue manager.
        /// </summary>
        IAimpPlaybackQueueService PlaybackQueueManager { get; }

        /// <summary>
        /// Gets the service options dialog.
        /// </summary>
        IAimpServiceOptionsDialog ServiceOptionsDialog { get; }

        /// <summary>
        /// Gets the service message dispatcher.
        /// </summary>
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
        /// Gets the current player state <see cref="AimpPlayerState"/>.
        /// </summary>
        /// <value>The state.</value>
        AimpPlayerState State { get; }

        /// <summary>
        /// Gets the current playing file.
        /// </summary>
        IAimpFileInfo CurrentFileInfo { get; }

        /// <summary>
        /// Gets the current play list item.
        /// </summary>
        /// <value>
        /// The current play list item.
        /// </value>
        IAimpPlaylistItem CurrentPlaylistItem { get; }

        /// <summary>
        /// Gets the win32 manager.
        /// </summary>
        IWin32Manager Win32Manager { get; }

        IAimpServiceSynchronizer ServiceSynchronizer { get; }

        IAimpServiceThreadPool ServiceThreadPool { get; }

        IAimpServiceMusicLibrary ServiceMusicLibrary { get; }

        IAimpServiceMusicLibraryUI ServiceMusicLibraryUi { get; }

        IAimpServiceFileFormats ServiceFileFormats { get; }

        IAimpServiceFileInfo ServiceFileInfo { get; }

        IAimpServiceFileSystems ServiceFileSystems { get; }

        IAimpServiceFileStreaming ServiceFileStreaming { get; }

        /// <summary>
        /// Gets the file information formatter service.
        /// </summary>
        IAimpServiceFileInfoFormatter ServiceFileInfoFormatter { get; }

        IAimpServiceFileTagEditor ServiceFileTagEditor { get; }

        IAimpServiceLyrics ServiceLyrics { get; }

        /// <summary>
        /// Pauses player.
        /// </summary>
        AimpActionResult Pause();

        /// <summary>
        /// Resumes player.
        /// </summary>
        AimpActionResult Resume();

        /// <summary>
        /// Stops player.
        /// </summary>
        AimpActionResult Stop();

        /// <summary>
        /// Stops the after track.
        /// </summary>
        AimpActionResult StopAfterTrack();

        /// <summary>
        /// Goes to next track.
        /// </summary>
        AimpActionResult GoToNext();

        /// <summary>
        /// Goes to previous track.
        /// </summary>
        AimpActionResult GoToPrev();

        /// <summary>
        /// Plays the specified queue item.
        /// </summary>
        /// <param name="queueItem">The queue item.</param>
        AimpActionResult Play(IAimpPlaybackQueueItem queueItem);

        /// <summary>
        /// Plays the specified play list item.
        /// </summary>
        /// <param name="playlistItem">The play list item.</param>
        AimpActionResult Play(IAimpPlaylistItem playlistItem);

        /// <summary>
        /// Plays the specified play list.
        /// </summary>
        /// <param name="playList">The play list.</param>
        AimpActionResult Play(IAimpPlaylist playList);
    }
}