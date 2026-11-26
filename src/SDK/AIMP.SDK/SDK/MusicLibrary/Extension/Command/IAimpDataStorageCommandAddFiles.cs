using System.Collections.Generic;

namespace AIMP.SDK.MusicLibrary.Extension.Command;

/// <summary>
/// Interface IAimpDataStorageCommandAddFiles
/// </summary>
public interface IAimpDataStorageCommandAddFiles
{
    /// <summary>
    /// Adds the specified files.
    /// </summary>
    /// <param name="files">List of the file names.</param>
    /// <returns>AimpActionResult.</returns>
    AimpActionResult Add(IList<string> files);
}