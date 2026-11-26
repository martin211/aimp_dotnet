namespace AIMP.SDK.MusicLibrary;

/// <summary>
/// Provides an access to data of UI elements for an active data storage that uses by the user.
/// Implements the <see cref="AIMP.SDK.IAimpService" />
/// </summary>
/// <seealso cref="AIMP.SDK.IAimpService" />
public interface IAimpServiceMusicLibraryUI : IAimpService
{
    /// <summary>
    /// Gets the file list from table view.
    /// </summary>
    /// <param name="flags">The flags.</param>
    /// <returns>AimpActionResult&lt;IAimpFileList&gt;.</returns>
    AimpActionResult<IAimpFileList> GetFiles(FilesType flags);

    /// <summary>
    /// Gets the grouping filter.
    /// </summary>
    /// <returns>AimpActionResult&lt;IAimpDataFilter&gt;.</returns>
    AimpActionResult<IAimpDataFilter> GetGroupingFilter();

    /// <summary>
    /// Gets the grouping filter path.
    /// </summary>
    /// <returns>AimpActionResult&lt;System.String&gt;.</returns>
    AimpActionResult<string> GetGroupingFilterPath();

    /// <summary>
    /// Sets the grouping filter path.
    /// </summary>
    /// <param name="path">The path.</param>
    /// <returns>AimpActionResult.</returns>
    AimpActionResult SetGroupingFilterPath(string path);
}