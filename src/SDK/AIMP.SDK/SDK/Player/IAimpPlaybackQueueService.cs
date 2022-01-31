﻿// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using AIMP.SDK.Player.Objects;

namespace AIMP.SDK.Player
{
    /// <summary>
    /// Interface IAimpServicePlaybackQueue
    /// Implements the <see cref="AIMP.SDK.IAimpService" />
    /// </summary>
    /// <seealso cref="AIMP.SDK.IAimpService" />
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
