using System;
using AIMP.SDK.FileManager.Objects;

namespace AIMP.SDK.PlayList.Objects;

/// <summary>
/// Enum PlaylistFlags
/// </summary>
[Flags]
public enum PlaylistFlags
{
    /// <summary>
    /// suppresses file format checking.
    /// </summary>
    NoCheckFormat = 1,

    /// <summary>
    /// suppresses file expansion to few virtual files.
    /// </summary>
    NoExpand = 2,

    /// <summary>
    /// File adding will be processed in main thread, the method will not return control until operation has been completed
    /// (not recommended).
    /// </summary>
    NoAsync = 4,

    /// <summary>
    /// Shows that object is <see cref="IAimpFileInfo" /> (otherwise object must be a string).
    /// </summary>
    FileInfo = 8
}