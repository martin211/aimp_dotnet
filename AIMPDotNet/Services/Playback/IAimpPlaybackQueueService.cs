namespace AIMP.SDK.Services.Playback
{
    public interface IAimpPlaybackQueueService : IAimpExtensionPlayerHook
    {
        IAimpPlaybackQueueItem GetNextTrack();

        IAimpPlaybackQueueItem GetPrevTrack();
    }
}