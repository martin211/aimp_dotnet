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

namespace AIMP.SDK.Playback
{
    public enum PlaybackQueueFlags
    {
        StartFromBeginning = 1,
        StartFromCursor = 2,
        StartFromItem = 3
    }

    public interface IAimpExtensionPlaybackQueue : IAimpExtension
    {
        bool GetNext(object current, PlaybackQueueFlags flags, IAimpPlaybackQueueItem queueItem);

        bool GetPrev(object current, PlaybackQueueFlags flags, IAimpPlaybackQueueItem queueItem);

        void OnSelect(IAimpPlaylistItem item, IAimpPlaybackQueueItem queueItem);
    }
}