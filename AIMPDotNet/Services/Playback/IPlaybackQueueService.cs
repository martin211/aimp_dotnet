using AIMP.SDK.Services.PlaybackManager;

namespace AIMP.SDK.Services.Playback
{
    public interface IPlaybackQueueService : IExtensionPlayerHook
    {
        IPlaybackQueueItem GetNextTrack();

        IPlaybackQueueItem GetPrevTrack();
    }
}