// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using System.IO;

namespace AIMP.SDK.FileManager.Commands
{
    public interface IAimpFileSystemCommandStreaming : IAimpFileSystemCommand
    {
        AimpActionResult<IAimpStream> CreateStream(string fileName, FileStreamingType flags, long offset, long size);
    }
}