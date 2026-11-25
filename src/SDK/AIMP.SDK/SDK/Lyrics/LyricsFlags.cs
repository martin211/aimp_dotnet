using System;

namespace AIMP.SDK.Lyrics;

/// <summary>
/// Enum LyricsFlags
/// </summary>
[Flags]
public enum LyricsFlags
{
    /// <summary>
    /// The none
    /// </summary>
    None = 0,

    /// <summary>
    /// Search without cache.
    /// </summary>
    Nocache = 1,

    /// <summary>
    /// The method will not return a control until the operation is completed.
    /// </summary>
    WaitFor = 4
}