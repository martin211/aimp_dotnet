namespace AIMP.SDK.Services.Player
{
    public interface IPlaybackQueueService
    {
        IPlaybackQueueItem GetNextTrack();

        IPlaybackQueueItem GetPrevTrack();
    }
}