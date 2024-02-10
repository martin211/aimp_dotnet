//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using AIMP.SDK.Playlist.Objects;

namespace AIMP.SDK.Player.Extensions;

/// <summary>
/// Extends an abilities of the <see cref="IAimpExtensionPlaybackQueue"/>.
/// </summary>
public interface IAimpExtensionPlaybackQueue2 : IAimpExtensionPlaybackQueue
{
    /// <summary>
    /// Returns information about the queue size and position of the Current item in it.
    /// </summary>
    AimpActionResult<PlaybackQueueInfo> GetInfo(IAimpPlaylistItem item);
}