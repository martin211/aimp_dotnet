namespace AIMP.SDK.Playback
{
    using AIMP.SDK.PlayList;

    public interface IAimpPlaybackQueueItem
    {
        object UserData { get; set; }

        IAimpPlayListItem PlayListItem { get; set; }
    }
}