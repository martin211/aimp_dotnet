using AIMP.SDK.FileManager.Objects;
using AIMP.SDK.Objects;

namespace AIMP.SDK.TagEditor;

/// <summary>
/// Provide possibility to access an file tag editor service.
/// Implements the <see cref="AIMP.SDK.IAimpService" />
/// </summary>
/// <seealso cref="AIMP.SDK.IAimpService" />
public interface IAimpServiceFileTagEditor : IAimpService
{
    /// <summary>
    /// Edits the file.
    /// </summary>
    /// <param name="filePath">The file path.</param>
    /// <returns>ActionResultType.</returns>
    AimpActionResult<IAimpFileTagEditor> EditFile(string filePath);

    /// <summary>
    /// Edits the file.
    /// </summary>
    /// <param name="fileStream">The file stream.</param>
    /// <returns>ActionResultType.</returns>
    AimpActionResult<IAimpFileTagEditor> EditFile(IAimpStream fileStream);

    /// <summary>
    /// Edits the tag.
    /// </summary>
    /// <param name="filePath">The file path.</param>
    /// <param name="tag">The tag.</param>
    /// <returns>ActionResultType.</returns>
    AimpActionResult<IAimpFileInfo> EditTag(string filePath, TagType tag);

    /// <summary>
    /// Edits the tag.
    /// </summary>
    /// <param name="fileStream">The file stream.</param>
    /// <param name="tag">The tag.</param>
    /// <returns>ActionResultType.</returns>
    AimpActionResult<IAimpFileInfo> EditTag(IAimpStream fileStream, TagType tag);
}