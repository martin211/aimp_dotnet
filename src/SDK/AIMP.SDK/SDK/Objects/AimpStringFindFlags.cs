using System;

namespace AIMP.SDK.Objects;

/// <summary>
/// Enum AimpStringFindFlags
/// </summary>
[Flags]
public enum AimpStringFindFlags
{
    /// <summary>
    /// The ignore case
    /// </summary>
    IgnoreCase = 1,

    /// <summary>
    /// The whole word
    /// </summary>
    WholeWord = 2
}