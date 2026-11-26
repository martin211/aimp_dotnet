namespace AIMP.SDK.FileManager;

/// <summary>
/// Extends <see cref="IAimpServiceFileURI2"/> with environment variable support (AIMP 6.0+).
/// </summary>
public interface IAimpServiceFileURI3 : IAimpServiceFileURI2
{
    /// <summary>
    /// Expands or collapses the known environment variables in a file URI.
    /// </summary>
    AimpActionResult<string> ProcessEnvironmentVariables(string fileUri, FileUriEnvironmentFlag flag);
}