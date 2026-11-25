using AIMP.SDK.FileManager.Objects;
using AIMP.SDK.Objects;

namespace AIMP.SDK.FileManager;

/// <summary>
/// Class CeateStreamResult.
/// </summary>
public class CreateStreamResult
{
    /// <summary>
    /// Initializes a new instance of the <see cref="CreateStreamResult" /> class.
    /// </summary>
    /// <param name="virtualFile">The virtual file.</param>
    /// <param name="stream">The stream.</param>
    public CreateStreamResult(IAimpVirtualFile virtualFile, IAimpStream stream)
    {
        VirtualFile = virtualFile;
        Stream = stream;
    }

    /// <summary>
    /// Gets the virtual file.
    /// </summary>
    /// <value>The virtual file.</value>
    public IAimpVirtualFile VirtualFile { get; }

    /// <summary>
    /// Gets the stream.
    /// </summary>
    /// <value>The stream.</value>
    public IAimpStream Stream { get; }
}