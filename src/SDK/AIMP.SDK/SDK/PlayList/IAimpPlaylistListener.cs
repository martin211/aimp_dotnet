namespace AIMP.SDK.PlayList;

/// <summary>
/// Interface provides an ability to receive notifications about changes in the playlist.
/// </summary>
public interface IAimpPlaylistListener
{
    /// <summary>
    /// Event occurs when playlist is activating.
    /// </summary>
    event AimpPlayListHandler Activated;

    /// <summary>
    /// Event occurs before deleting or unloading.
    /// </summary>
    event AimpPlayListHandler Removed;

    /// <summary>
    /// Occurs when playlist was changed.
    /// </summary>
    event PlayListChangedHandler Changed;

    /// <summary>
    /// Occurs when scanning begin.
    /// </summary>
    event AimpPlayListHandler ScanningBegin;

    /// <summary>
    /// Occurs during scanning progress.
    /// </summary>
    event AimpPlayListHandler<ScanningProgressEventArgs> ScanningProgress;

    /// <summary>
    /// Occurs when scanning end.
    /// </summary>
    event AimpPlayListHandler<ScanningEndEventArgs> ScanningEnd;
}