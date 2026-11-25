namespace AIMP.SDK.PlayList.Objects;

/// <summary>
/// Playlist sort types.
/// </summary>
public enum PlaylistSort
{
    /// <summary>
    /// By title.
    /// </summary>
    Title = 1,

    /// <summary>
    /// By file name.
    /// </summary>
    FileName = 2,

    /// <summary>
    /// By duration.
    /// </summary>
    Duration = 3,

    /// <summary>
    /// By artist
    /// </summary>
    Artist = 4,

    /// <summary>
    /// Inverse.
    /// </summary>
    Inverse = 5,

    /// <summary>
    /// Randomize.
    /// </summary>
    Randomize = 6,

    /// <summary>
    /// Randomize by group.
    /// </summary>
    RandomizeGroup = 7,

    /// <summary>
    /// Randomize by group items.
    /// </summary>
    RandomizeGroupItems = 8,

    /// <summary>
    /// Randomize by group and group items.
    /// </summary>
    RandomizeGroupsAndItems = 9
}