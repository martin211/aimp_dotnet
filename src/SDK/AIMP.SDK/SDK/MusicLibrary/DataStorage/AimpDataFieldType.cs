namespace AIMP.SDK.MusicLibrary.DataStorage;

/// <summary>
/// Enum AimpDataFieldType
/// </summary>
public enum AimpDataFieldType
{
    /// <summary>
    /// The none
    /// </summary>
    None = 0,

    /// <summary>
    /// The int32
    /// </summary>
    Int32 = 1,

    /// <summary>
    /// The int64
    /// </summary>
    Int64 = 2,

    /// <summary>
    /// The float
    /// </summary>
    Float = 3,

    /// <summary>
    /// The string
    /// </summary>
    String = 4,

    /// <summary>
    /// Set of string values divided by ";" character.
    /// </summary>
    StringSet = 5,

    /// <summary>
    /// Display value is formatted data time value (format string is depended from the context).
    /// </summary>
    DateTime = 10,

    /// <summary>
    /// Display value is formatted time value (format string is depended from the context).
    /// </summary>
    Duration = 11,

    /// <summary>
    /// Display value is formatted file size value (format string is depended from the context).
    /// </summary>
    FileSize = 12,

    /// <summary>
    /// Grouping tree split the value by levels by the "\" and "/" characters. Grouping by this field with other fields is
    /// not available.
    /// </summary>
    FileName = 13
}