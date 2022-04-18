using AIMP.SDK.FileManager.Objects;
using AIMP.SDK.Player.Objects;
using AIMP.SDK.Playlist.Objects;

namespace AIMP.SDK.Player
{
    public enum ActionOnTrackEnd
    {
        None = 0,
        /// <summary>
        /// Jump to next track and stop playback.
        /// </summary>
        GoToNextAndStop = 1,
        /// <summary>
        /// Jump to next track and suspend playback.
        /// </summary>
        GoToNextAndPause = 2
    }

    /// <summary>
    /// This service provides an access to playback control interface.
    /// </summary>
    /// <seealso cref="IAimpServicePlayer2" />
    /// <seealso cref="AIMP.SDK.IAimpService" />
    public interface IAimpServicePlayer : IAimpServicePlayer2, IAimpService
    {
        /// <summary>
        /// Gets the current player state <see cref="AimpPlayerState" />.
        /// </summary>
        /// <value>The state.</value>
        AimpPlayerState State { get; }

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
        /// Gets or sets the volume.
        /// </summary>
        /// <value>The volume.</value>
        float Volume { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether the volume is mute.
        /// </summary>
        /// <value><c>true</c> if this instance is mute; otherwise, <c>false</c>.</value>
        bool IsMute { get; set; }

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

        ActionOnTrackEnd ActionOnEndOfTrack { get; set; }

        /// <summary>
        /// Provides an ability to start playing a next track when current is end.
        /// </summary>
        bool AutoJumpToNextTrack { get; set; }

        /// <summary>
        /// Provides an ability to switch off all effects when switching between tracks automatically.
        /// </summary>
        bool AutoSwitching { get; set; }

        /// <summary>
        /// Gets or sets the automatic switching pause between tracks.
        /// In milliseconds. 0 - switched off. 
        /// </summary>
        int AutoSwitchingPauseBetweenTracks { get; set; }

        /// <summary>
        /// Time of cross fade effect when switching between tracks automatically, In milliseconds. 0 - switched off.
        /// </summary>
        int AutoSwitchingCrossFade { get; set; }

        /// <summary>
        /// Time of volume fade in effect at beginning of track when switching between tracks automatically, in milliseconds. 0 - switched off.
        /// </summary>
        int AutoSwitchingFadeIn { get; set; }

        /// <summary>
        /// Time of volume fade out effect at ending of track when switching between tracks automatically, in milliseconds. 0 - switched off.
        /// </summary>
        int AutoSwitchingFadeOut { get; set; }

        /// <summary>
        /// Provides an ability to switch off all effects when switching between tracks manually. 
        /// </summary>
        bool ManualSwitching { get; set; }

        /// <summary>
        /// Time of cross fade effect when switching between tracks manually, In milliseconds. 0 - switched off.
        /// </summary>
        int ManualSwitchingCrossFade { get; set; }

        /// <summary>
        /// Time of volume fade in effect at beginning of track when switching between tracks manually, in milliseconds. 0 - switched off.
        /// </summary>
        int ManualSwitchingFadeIn { get; set; }

        /// <summary>
        /// Time of volume fade out effect at ending of track when switching between tracks manually, in milliseconds. 0 - switched off.
        /// </summary>
        int ManualSwitchingFadeOut { get; set; }

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

        /// <summary>
        /// Plays the specified file URI.
        /// </summary>
        /// <param name="fileUri">Can be file path to playlist.</param>
        /// <param name="flags">The flags.</param>
        /// <note>
        /// Note 1: Note that function doesn't check if file playback really started. It just put the file into queue of loading thread (Refer to the AIMP_MSG_EVENT_STREAM_START).
        /// Note 2: the method returns E_FAIL if file does not correspond to conditions that specified via flags.
        /// Note 3: if FileURI contains path to the playlist file, the WithoutAdding flag ignored, because player cannot start playlist playback without importing it.
        /// </note>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Play(string fileUri, PlayFlags flags);

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
    }
}