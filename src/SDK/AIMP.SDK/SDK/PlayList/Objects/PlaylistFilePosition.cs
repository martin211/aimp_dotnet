namespace AIMP.SDK.PlayList.Objects;

/// <summary>
/// Enum PlaylistFilePosition
/// </summary>
public enum PlaylistFilePosition
{
    /// <summary>
    /// Adding the records to random position
    /// </summary>
    RandomPosition = -2,

    /// <summary>
    /// Adding the records to the end of playlist.
    /// </summary>
    EndPosition = -1,

    /// <summary>
    /// Adding the records to the specified position.
    /// </summary>
    CurrentPosition = 0
}