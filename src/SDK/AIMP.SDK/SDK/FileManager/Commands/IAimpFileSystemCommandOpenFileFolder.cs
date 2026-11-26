namespace AIMP.SDK.FileManager.Commands;

/// <summary>
/// Interface IAimpFileSystemCommandOpenFileFolder
/// Implements the <see cref="AIMP.SDK.FileManager.Commands.IAimpFileSystemCustomFileCommand" />
/// </summary>
/// <seealso cref="AIMP.SDK.FileManager.Commands.IAimpFileSystemCustomFileCommand" />
public interface IAimpFileSystemCommandOpenFileFolder : IAimpFileSystemCustomFileCommand
{
    /// <summary>
    /// Determines whether this instance can process the specified file.
    /// </summary>
    /// <param name="file">The file.</param>
    /// <returns>AimpActionResult.</returns>
    AimpActionResult CanProcess(string file);

    /// <summary>
    /// Processes the specified file.
    /// </summary>
    /// <param name="file">The file.</param>
    /// <returns>AimpActionResult.</returns>
    AimpActionResult Process(string file);
}