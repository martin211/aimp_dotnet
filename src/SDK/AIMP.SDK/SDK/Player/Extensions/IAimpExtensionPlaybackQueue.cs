//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using AIMP.SDK.Player.Objects;
using AIMP.SDK.Playlist.Objects;

namespace AIMP.SDK.Player.Extensions
{
    /// <summary>
    /// Enum PlaybackQueueFlags
    /// </summary>
    public enum PlaybackQueueFlags
    {
        /// <summary>
        /// The start from beginning
        /// </summary>
        StartFromBeginning = 1,

        /// <summary>
        /// The start from cursor
        /// </summary>
        StartFromCursor = 2,

        /// <summary>
        /// The start from item
        /// </summary>
        StartFromItem = 3
    }

    /// <summary>
    /// Interface IAimpExtensionPlaybackQueue
    /// Implements the <see cref="AIMP.SDK.IAimpExtension" />
    /// </summary>
    /// <seealso cref="AIMP.SDK.IAimpExtension" />
    public interface IAimpExtensionPlaybackQueue : IAimpExtension
    {
        /// <summary>
        /// Gets the next.
        /// </summary>
        /// <param name="current">The current.</param>
        /// <param name="flags">The flags.</param>
        /// <param name="queueItem">The queue item.</param>
        /// <returns><c>true</c> if XXXX, <c>false</c> otherwise.</returns>
        AimpActionResult GetNext(object current, PlaybackQueueFlags flags, IAimpPlaybackQueueItem queueItem);

        /// <summary>
        /// Gets the previous.
        /// </summary>
        /// <param name="current">The current.</param>
        /// <param name="flags">The flags.</param>
        /// <param name="queueItem">The queue item.</param>
        /// <returns><c>true</c> if XXXX, <c>false</c> otherwise.</returns>
        AimpActionResult GetPrev(object current, PlaybackQueueFlags flags, IAimpPlaybackQueueItem queueItem);

        /// <summary>
        /// Called when [select].
        /// </summary>
        /// <param name="item">The item.</param>
        /// <param name="queueItem">The queue item.</param>
        void OnSelect(IAimpPlaylistItem item, IAimpPlaybackQueueItem queueItem);
    }
}
