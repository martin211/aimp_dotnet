namespace AIMP.SDK.MusicLibrary.Extension.Command;

/// <summary>
/// Interface IAimpDataStorageCommandUserMark
/// </summary>
public interface IAimpDataStorageCommandUserMark
{
    /// <summary>
    /// Sets the mark.
    /// </summary>
    /// <param name="id">The identifier.</param>
    /// <param name="value">The value.</param>
    /// <returns>AimpActionResult.</returns>
    AimpActionResult SetMark(object id, double value);
}