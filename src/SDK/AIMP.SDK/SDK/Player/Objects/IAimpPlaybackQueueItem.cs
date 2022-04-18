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

using AIMP.SDK.Playlist;
using AIMP.SDK.Playlist.Objects;

<<<<<<<< HEAD:src/SDK/AIMP.SDK/SDK/Primitives/IAimpPlaybackQueueItem.cs
namespace AIMP.SDK.Player.Primitives
========
namespace AIMP.SDK.Player.Objects
>>>>>>>> release/5.02.2365.1:src/SDK/AIMP.SDK/SDK/Player/Objects/IAimpPlaybackQueueItem.cs
{
    /// <summary>
    /// Interface IAimpPlaybackQueueItem
    /// </summary>
    public interface IAimpPlaybackQueueItem
    {
        /// <summary>
        /// Gets or sets the user data.
        /// </summary>
        /// <value>The user data.</value>
        object UserData { get; set; }

        /// <summary>
        /// Gets or sets the playlist item.
        /// </summary>
        /// <value>The playlist item.</value>
        IAimpPlaylistItem PlaylistItem { get; set; }
    }
}
