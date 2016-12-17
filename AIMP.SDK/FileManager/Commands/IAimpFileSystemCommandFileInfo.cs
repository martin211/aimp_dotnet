namespace AIMP.SDK.FileManager.Commands
{
    public interface IAimpFileSystemCommandFileInfo : IAimpFileSystemCommand
    {
        AimpActionResult GetFileAttrs(string file, out object attr);

        AimpActionResult GetFileSize(string file, out long size);

        AimpActionResult IsFileExists(string file);
    }
}