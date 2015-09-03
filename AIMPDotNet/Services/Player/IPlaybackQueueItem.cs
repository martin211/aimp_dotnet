using AIMP.SDK.Services.PlayListManager;

namespace AIMP.SDK.Services.Player
{
    public interface IPlaybackQueueItem
    {
        object UserData { get; set; }

        IAimpPlayListItem PlayListItem { get; set; }
    }
}