namespace AIMP.SDK.Playback
{
    public interface IAimpPlaybackQueueService : IAimpExtensionPlayerHook
    {
        IAimpPlaybackQueueItem GetNextTrack();

        IAimpPlaybackQueueItem GetPrevTrack();
    }
}