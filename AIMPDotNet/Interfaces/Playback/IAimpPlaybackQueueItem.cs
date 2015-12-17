namespace AIMP.SDK.Services.Playback
{
    using AIMP.SDK.Services.PlayList;

    public interface IAimpPlaybackQueueItem
    {
        object UserData { get; set; }

        IAimpPlayListItem PlayListItem { get; set; }
    }
}