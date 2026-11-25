using System;

namespace AIMP.SDK.FileManager;

/// <summary>
/// Enum FileFormats
/// </summary>
[Flags]
public enum FileFormats
{
    /// <summary>
    /// The aimp service fileformats category audio
    /// </summary>
    Audio = 1,

    /// <summary>
    /// The aimp service fileformats category playlists
    /// </summary>
    Playlists = 2
}