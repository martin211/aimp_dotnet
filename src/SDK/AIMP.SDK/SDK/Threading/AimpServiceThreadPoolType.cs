namespace AIMP.SDK.Threading;

/// <summary>
/// Enum AimpServiceThreadPoolType
/// </summary>
public enum AimpServiceThreadPoolType
{
    /// <summary>
    /// The none
    /// </summary>
    None = 0,

    /// <summary>
    /// the method will not return control until operation has been completed if this flag is used.
    /// </summary>
    WaitFor = 1
}