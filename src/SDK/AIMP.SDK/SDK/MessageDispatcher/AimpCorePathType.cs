namespace AIMP.SDK.MessageDispatcher;

/// <summary>
/// Path type.
/// </summary>
public enum AimpCorePathType
{
    /// <summary>
    /// Path to audiolibrary.
    /// </summary>
    Audiolibrary = 6,

    /// <summary>
    /// Path to encoders.
    /// </summary>
    [System.Obsolete("Removed in AIMP 6.0.")]
    Encoders = 8,

    /// <summary>
    /// Path to help files.
    /// </summary>
    Help = 9,

    /// <summary>
    /// Path to icons.
    /// </summary>
    Icons = 5,

    /// <summary>
    /// Path to language files.
    /// </summary>
    Langs = 2,

    /// <summary>
    /// Path to playlist.
    /// </summary>
    Playlists = 1,

    /// <summary>
    /// Path to plugins.
    /// </summary>
    Plugins = 4,

    /// <summary>
    /// Path to profile.
    /// </summary>
    Profile = 0,

    /// <summary>
    /// Path to skins.
    /// </summary>
    Skins = 3,

    /// <summary>
    /// Path to common skins.
    /// </summary>
    SkinsCommon = 11
}