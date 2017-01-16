using System.Collections.Generic;

namespace AIMP.SDK.FileManager.Commands
{
    public interface IAimpFileSystemCommandCopyToClipboard : IAimpFileSystemCommand
    {
        AimpActionResult CopyToClipboard(IList<string> files);
    }
}