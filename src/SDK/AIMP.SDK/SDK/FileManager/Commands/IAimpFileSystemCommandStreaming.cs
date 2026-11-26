using AIMP.SDK.Objects;

namespace AIMP.SDK.FileManager.Commands;

/// <summary>
/// Interface IAimpFileSystemCommandStreaming
/// Implements the <see cref="AIMP.SDK.FileManager.Commands.IAimpFileSystemCommand" />
/// </summary>
/// <seealso cref="AIMP.SDK.FileManager.Commands.IAimpFileSystemCommand" />
public interface IAimpFileSystemCommandStreaming : IAimpFileSystemCommand
{
    /// <summary>
    /// Creates the stream.
    /// </summary>
    /// <param name="fileName">Name of the file.</param>
    /// <param name="flags">The flags.</param>
    /// <param name="offset">The offset.</param>
    /// <param name="size">The size.</param>
    /// <returns>AimpActionResult&lt;IAimpStream&gt;.</returns>
    AimpActionResult<IAimpStream> CreateStream(string fileName, FileStreamingType flags, long offset, long size);
}