using AIMP.SDK.FileManager.Commands;

namespace AIMP.SDK.FileManager
{
    public interface IAimpServiceFileSystems
    {
        AimpActionResult Get<TCommand>(string fileUri, out TCommand command) where TCommand : IAimpFileSystemCommand;

        AimpActionResult GetDefault<TCommand>(out TCommand command) where TCommand : IAimpFileSystemCommand;
    }
}