namespace AIMP.SDK.Services.PlayListManager
{
    public interface IServicePlaybackQueue
    {
        IAimpPlaybackQueueItem GetNextTrack();

        IAimpPlaybackQueueItem GetPrevTrack();
    }
}