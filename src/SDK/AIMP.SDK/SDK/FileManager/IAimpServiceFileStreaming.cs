using AIMP.SDK.Objects;

namespace AIMP.SDK.FileManager;

/// <summary>
/// Interface IAimpServiceFileStreaming
/// Implements the <see cref="AIMP.SDK.IAimpService" />
/// </summary>
/// <seealso cref="AIMP.SDK.IAimpService" />
public interface IAimpServiceFileStreaming : IAimpService
{
    /// <summary>
    /// Creates the stream for file.
    /// </summary>
    /// <param name="fileName">Name of the file.</param>
    /// <param name="flags">The flags.</param>
    /// <param name="offset">The offset.</param>
    /// <param name="size">The size.</param>
    /// <returns>AimpActionResult&lt;IAimpStream&gt;.</returns>
    AimpActionResult<IAimpStream> CreateStreamForFile(string fileName, FileStreamingType flags, long offset,
        long size);

    /// <summary>
    /// Creates the stream for file URI.
    /// </summary>
    /// <param name="fileUrl">The file URL.</param>
    /// <returns>AimpActionResult&lt;CeateStreamResult&gt;.</returns>
    AimpActionResult<CreateStreamResult> CreateStreamForFileUri(string fileUrl);
}