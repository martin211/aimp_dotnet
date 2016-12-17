using System.IO;

namespace AIMP.SDK.FileManager.Commands
{
    public interface IAimpFileSystemCommandDropSource : IAimpFileSystemCommand
    {
        AimpActionResult CreateStream(string file, out Stream stream);
    }
}