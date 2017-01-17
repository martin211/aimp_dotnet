namespace AIMP.SDK.FileManager.Commands
{
    public interface IAimpFileSystemCustomFileCommand : IAimpFileSystemCommand
    {
        AimpActionResult CanProcess(string file);

        AimpActionResult Process(string file);
    }
}