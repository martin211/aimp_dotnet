// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

namespace AIMP.SDK.Playback
{
    public interface IAimpPlaybackQueueService : IAimpExtensionPlayerHook
    {
        IAimpPlaybackQueueItem GetNextTrack();

        IAimpPlaybackQueueItem GetPrevTrack();
    }
}