namespace AIMP.SDK.MusicLibrary.Extension.Command;

/// <summary>
/// Interface IAimpDataStorageCommandDeleteFiles
/// </summary>
public interface IAimpDataStorageCommandDeleteFiles
{
    /// <summary>
    /// Determines whether this instance can delete the specified physically.
    /// </summary>
    /// <param name="physically">if set to <c>true</c> [physically].</param>
    /// <returns><c>true</c> if this instance can delete the specified physically; otherwise, <c>false</c>.</returns>
    bool CanDelete(bool physically);

    /// <summary>
    /// Deletes the specified files.
    /// </summary>
    /// <param name="files">The files.</param>
    /// <param name="physically">if set to <c>true</c> [physically].</param>
    /// <returns>AimpActionResult.</returns>
    AimpActionResult Delete(IAimpFileList files, bool physically);
}