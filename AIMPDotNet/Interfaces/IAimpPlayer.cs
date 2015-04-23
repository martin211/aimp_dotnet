﻿using System;
using AIMP.SDK.Services.AlbumArtManager;
using AIMP.SDK.Services.MenuManager;
using AIMP.SDK.Services.PlayListManager;

namespace AIMP.SDK.Interfaces
{
    using Services.Win32Manager;

    using Services.ActionManager;
    using Services.ConfigurationManager;
    using Services.MUIManager;

    /// <summary>
    /// 
    /// </summary>
    /// <param name="state"></param>
    public delegate void AimpStateChanged(PlayerState state);

    /// <summary>
    /// Interface IAIMPPlayer
    /// </summary>
    public interface IAimpPlayer : IDisposable
    {
        /// <summary>
        /// Occurs when player state has been changed.
        /// </summary>
        event AimpStateChanged StateChanged;

        /// <summary>
        /// Occurs when AIMP language has been changed.
        /// </summary>
        event EventHandler LanguageChanged;

        event EventHandler TrackChanged;

        /// <summary>
        /// Gets Player core.
        /// </summary>
        IAimpCore Core { get; }

        /// <summary>
        /// Gets player menu manager.
        /// </summary>
        IMenuManager MenuManager { get; }

        /// <summary>
        /// Gets player action manager.
        /// </summary>
        IActionManager ActionManager { get; }

        /// <summary>
        /// Gets the MUI manager.
        /// </summary>
        // ReSharper disable InconsistentNaming
        IMUIManager MUIManager { get; }
        // ReSharper restore InconsistentNaming

        /// <summary>
        /// Gets the album art manager.
        /// </summary>
        IAlbumArtManager AlbumArtManager { get; }

        /// <summary>
        /// Gets the configuration manager.
        /// </summary>
        IConfigurationManager ConfigurationManager { get; }

        IPlayListManager PlayListManager { get; }

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
        /// Gets the current player state <see cref="PlayerState"/>.
        /// </summary>
        /// <value>The state.</value>
        PlayerState State { get; }

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
        IAimpPlayListItem CurrentPlayListItem { get; }

        /// <summary>
        /// Gets the win32 manager.
        /// </summary>
        IWin32Manager Win32Manager { get; }

        /// <summary>
        /// Pauses player.
        /// </summary>
        void Pause();

        /// <summary>
        /// Resumes player.
        /// </summary>
        void Resume();

        /// <summary>
        /// Stops player.
        /// </summary>
        void Stop();

        /// <summary>
        /// Stops the after track.
        /// </summary>
        void StopAfterTrack();

        void GoToNext();

        void GoToPrev();

        /// <summary>
        /// Plays the specified queue item.
        /// </summary>
        /// <param name="queueItem">The queue item.</param>
        void Play(IAimpPlaybackQueueItem queueItem);

        /// <summary>
        /// Plays the specified play list item.
        /// </summary>
        /// <param name="playListItem">The play list item.</param>
        void Play(IAimpPlayListItem playListItem);

        /// <summary>
        /// Plays the specified play list.
        /// </summary>
        /// <param name="playList">The play list.</param>
        void Play(IAimpPlayList playList);
    }
}