using System;

namespace AIMP.SDK.FileManager;

/// <summary>
/// Enum FileStreamingType
/// </summary>
[Flags]
public enum FileStreamingType
{
    /// <summary>
    /// The aimp service filestreaming flag read
    /// </summary>
    Read = 0,

    /// <summary>
    /// The aimp service filestreaming flag createnew
    /// </summary>
    CreateNew = 1,

    /// <summary>
    /// The aimp service filestreaming flag readwrite
    /// </summary>
    ReadWrite = 2,

    /// <summary>
    /// The aimp service filestreaming flag maptomemory
    /// </summary>
    MapToMemory = 4
}