namespace AIMP.SDK.Core;

/// <summary>
/// Access to the player log (AIMP 6.0+).
/// </summary>
public interface IAimpServiceLog : IAimpService
{
    /// <summary>
    /// Adds a Unicode message to the player log.
    /// </summary>
    void Add(string message);

    /// <summary>
    /// Adds a Unicode message to the player log with the specified flags.
    /// </summary>
    void Add(string message, uint flags);
}