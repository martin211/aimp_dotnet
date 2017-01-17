using System;

namespace AIMP.SDK.FileManager.Commands
{
    public interface IAimpFileSystemCommandStreaming : IAimpFileSystemCommand
    {
        AimpActionResult CreateStream(string fileName, FileStreamingType flags, long offset, long size, out IAimpStream stream);
    }
}