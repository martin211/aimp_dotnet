namespace AIMP.SDK.MusicLibrary.DataFilter;

/// <summary>
/// Enum FieldFilterOperationType
/// </summary>
public enum FieldFilterOperationType
{
    /// <summary>
    /// The equals
    /// </summary>
    Equals = 0,

    /// <summary>
    /// The not equals
    /// </summary>
    NotEquals = 1,

    /// <summary>
    /// The between
    /// </summary>
    Between = 2,

    /// <summary>
    /// The less than
    /// </summary>
    LessThan = 3,

    /// <summary>
    /// The less than or equals
    /// </summary>
    LessThanOrEquals = 4,

    /// <summary>
    /// The greater than
    /// </summary>
    GreaterThan = 5,

    /// <summary>
    /// The greater than or equals
    /// </summary>
    GreaterThanOrEquals = 6,

    /// <summary>
    /// Determines whether this instance contains the object.
    /// </summary>
    Contains = 7,

    /// <summary>
    /// The begins with
    /// </summary>
    BeginsWith = 8,

    /// <summary>
    /// The ends with
    /// </summary>
    EndsWith = 9,

    IsLastXDays = 10,

    /// <summary>
    /// Does not contain (AIMP 6.0+).
    /// </summary>
    DoesNotContain = 11,
}