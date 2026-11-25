namespace AIMP.SDK.Objects;

/// <summary>
/// IAimpFileStream is extended variant of IAimpStream specially for file-based streams.
/// Implements the <see cref="IAimpStream" /></summary>
/// <seealso cref="IAimpStream" />
public interface IAimpFileStream : IAimpStream
{
    /// <summary>
    /// If file is clipped the method will return clipping bounds. See the IAimpServiceFileStreaming.CreateStreamForFile.
    /// </summary>
    /// <returns>AimpActionResult.</returns>
    AimpActionResult<Clipping> GetClipping();

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    AimpActionResult<IAimpString> GetFileName();
}