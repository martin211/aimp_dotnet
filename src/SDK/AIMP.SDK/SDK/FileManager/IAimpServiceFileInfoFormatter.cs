using AIMP.SDK.FileManager.Objects;

namespace AIMP.SDK.FileManager;

/// <summary>
/// Service provides an ability to format file information with specified template.
/// Implements the <see cref="AIMP.SDK.IAimpService" />
/// </summary>
/// <seealso cref="AIMP.SDK.IAimpService" />
public interface IAimpServiceFileInfoFormatter : IAimpService
{
    /// <summary>
    /// Formats the specified template.
    /// </summary>
    /// <param name="template">The list of supported macros for template depends from version of application.</param>
    /// <param name="fileInfo">The file information.</param>
    /// <returns>AimpActionResult&lt;System.String&gt;.</returns>
    AimpActionResult<string> Format(string template, IAimpFileInfo fileInfo);

    /// <summary>
    /// Formats the specified template with the formatter ID
    /// (see <see cref="AimpFileInfoFormatterId"/>, AIMP 6.0+).
    /// </summary>
    AimpActionResult<string> Format(string template, IAimpFileInfo fileInfo, int formatterId);
}