//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using AIMP.SDK.Player.Objects;

namespace AIMP.SDK.Player
{
    /// <summary>
    /// Service provides an access to internal playback queue (do not confuse with <see cref="AIMP.SDK.Playlist.IAimpPlaylistQueue"/>).
    /// Internal playback queue based (by default) on content of playlist and state of the "Shuffle" mode, but can be overridden by plugin via an extension for the IAIMPServicePlaybackQueue service.
    /// </summary>
    public interface IAimpServicePlaybackQueue : IAimpServicePlaybackQueue2, IAimpService
    {
        /// <summary>
        /// Gets the next track.
        /// </summary>
        /// <returns>AimpActionResult&lt;IAimpPlaybackQueueItem&gt;.</returns>
        AimpActionResult<IAimpPlaybackQueueItem> GetNextTrack();

        /// <summary>
        /// Gets the previous track.
        /// </summary>
        /// <returns>AimpActionResult&lt;IAimpPlaybackQueueItem&gt;.</returns>
        AimpActionResult<IAimpPlaybackQueueItem> GetPrevTrack();
    }
}
