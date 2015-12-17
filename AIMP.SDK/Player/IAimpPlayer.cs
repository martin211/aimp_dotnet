namespace AIMP.SDK.Player
{
    using System;

    using AIMP.SDK.ActionManager;
    using AIMP.SDK.AlbumArtManager;
    using AIMP.SDK.ConfigurationManager;
    using AIMP.SDK.MenuManager;
    using AIMP.SDK.MUIManager;
    using AIMP.SDK.Options;
    using AIMP.SDK.Playback;
    using AIMP.SDK.PlayList;
    using AIMP.SDK.Win32;

    /// <summary>
    /// Player state changed event.
    /// </summary>
    public class StateChangedEventArgs : EventArgs
    {
        /// <summary>
        /// Gets the state of the player.
        /// </summary>
        public AimpPlayerState PlayerState { get; private set; }

        /// <summary>
        /// Initializes a new instance of the <see cref="T:System.EventArgs"/> class.
        /// </summary>
        public StateChangedEventArgs(AimpPlayerState playerState)
        {
            PlayerState = playerState;
        }
    }

    /// <summary>
    /// Interface IAIMPPlayer
    /// </summary>
    public interface IAimpPlayer : IDisposable
    {
        /// <summary>
        /// Occurs when player state has been changed.
        /// </summary>
        event EventHandler<StateChangedEventArgs> StateChanged;

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
        IAimpMenuManager MenuManager { get; }

        /// <summary>
        /// Gets player action manager.
        /// </summary>
        IAimpActionManager ActionManager { get; }

        /// <summary>
        /// Gets the MUI manager.
        /// </summary>
        // ReSharper disable InconsistentNaming
        IAimpMUIManager MUIManager { get; }
        // ReSharper restore InconsistentNaming

        /// <summary>
        /// Gets the album art manager.
        /// </summary>
        IAimpAlbumArtManager AlbumArtManager { get; }

        /// <summary>
        /// Gets the configuration manager.
        /// </summary>
        IAimpConfigurationManager ConfigurationManager { get; }

        /// <summary>
        /// Gets the play list manager.
        /// </summary>
        IAimpPlayListManager PlayListManager { get; }

        /// <summary>
        /// Gets the playback queue manager.
        /// </summary>
        IAimpPlaybackQueueService PlaybackQueueManager { get; }

        IAimpServiceOptionsDialog ServiceOptionsDialog { get; }

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

        /// <summary>
        /// Goes to next track.
        /// </summary>
        void GoToNext();

        /// <summary>
        /// Goes to previous track.
        /// </summary>
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