namespace AIMP.SDK.FileManager;

public interface IAimpServiceFileURI2 : IAimpServiceFileURI
{
    AimpActionResult<string> GetScheme(string fileUri);
}