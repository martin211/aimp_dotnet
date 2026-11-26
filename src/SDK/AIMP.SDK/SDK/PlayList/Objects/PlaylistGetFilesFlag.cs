using System;

namespace AIMP.SDK.PlayList.Objects;

/// <summary>
/// Enum PlaylistGetFilesFlag
/// </summary>
[Flags]
public enum PlaylistGetFilesFlag
{
    /// <summary>
    /// All
    /// </summary>
    All = 0,

    /// <summary>
    /// The selected only
    /// </summary>
    SelectedOnly = 0x1,

    /// <summary>
    /// The visible only
    /// </summary>
    VisibleOnly = 0x2,

    /// <summary>
    /// In this case, the file-container will be added to the list if playlist item is virtual file.
    /// </summary>
    CollapseVirtual = 0x4
}