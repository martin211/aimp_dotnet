namespace AIMP.SDK.MusicLibrary.DataFilter;

/// <summary>
/// Enum FilterGroupOperationType
/// </summary>
public enum FilterGroupOperationType
{
    /// <summary>
    /// The or
    /// </summary>
    Or = 0,

    /// <summary>
    /// The and
    /// </summary>
    And = 1,

    /// <summary>
    /// The not or
    /// </summary>
    NotOr = 2,

    /// <summary>
    /// The not and
    /// </summary>
    NotAnd = 3
}