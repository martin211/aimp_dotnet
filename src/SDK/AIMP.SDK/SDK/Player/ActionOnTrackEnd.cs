namespace AIMP.SDK.Player;

public enum ActionOnTrackEnd
{
    None = 0,

    /// <summary>
    /// Jump to next track and stop playback.
    /// </summary>
    GoToNextAndStop = 1,

    /// <summary>
    /// Jump to next track and suspend playback.
    /// </summary>
    GoToNextAndPause = 2
}