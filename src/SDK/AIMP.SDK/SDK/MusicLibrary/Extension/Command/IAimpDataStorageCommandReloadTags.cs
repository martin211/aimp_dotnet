namespace AIMP.SDK.MusicLibrary.Extension.Command;

/// <summary>
/// Interface IAimpDataStorageCommandReloadTags
/// </summary>
public interface IAimpDataStorageCommandReloadTags
{
    /// <summary>
    /// Reloads the tags.
    /// </summary>
    /// <param name="files">The files.</param>
    /// <returns>AimpActionResult.</returns>
    AimpActionResult ReloadTags(IAimpFileList files);
}