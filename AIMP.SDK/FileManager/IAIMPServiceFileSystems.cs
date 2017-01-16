using AIMP.SDK.FileManager.Commands;

namespace AIMP.SDK.FileManager
{
    public interface IAimpServiceFileSystems
    {
        AimpActionResult Get<TCommand>(string fileUri, out IAimpFileSystemCommand command);

        AimpActionResult GetDefault<TCommand>(out IAimpFileSystemCommand command);
    }
}