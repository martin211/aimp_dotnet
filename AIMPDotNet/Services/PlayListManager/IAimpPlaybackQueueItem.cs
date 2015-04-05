namespace AIMP.SDK.Services.PlayListManager
{
    using System;

    public interface IAimpPlaybackQueueItem
    {
        Object UserData { get; set; }

        IAimpPlayListItem PlayListItem { get; set; }
    }
}