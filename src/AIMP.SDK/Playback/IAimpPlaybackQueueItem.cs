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
using AIMP.SDK.Playlist;

namespace AIMP.SDK.Playback
{
    public interface IAimpPlaybackQueueItem
    {
        object UserData { get; set; }

        IAimpPlaylistItem PlaylistItem { get; set; }
    }
}