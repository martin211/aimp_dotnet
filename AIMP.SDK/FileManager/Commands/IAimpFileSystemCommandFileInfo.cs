namespace AIMP.SDK.FileManager.Commands
{
    public interface IAimpFileSystemCommandFileInfo : IAimpFileSystemCommand
    {
        AimpActionResult GetFileAttrs(string file, out AimpFileAttributes attr);

        AimpActionResult GetFileSize(string file, out long size);

        AimpActionResult IsFileExists(string file);
    }
}