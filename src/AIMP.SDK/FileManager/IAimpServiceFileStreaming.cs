// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------
using System;

namespace AIMP.SDK.FileManager
{
    [Flags]
    public enum FileStreamingType
    {
        AIMP_SERVICE_FILESTREAMING_FLAG_READ = 0,
        AIMP_SERVICE_FILESTREAMING_FLAG_CREATENEW = 1,
        AIMP_SERVICE_FILESTREAMING_FLAG_READWRITE = 2,
        AIMP_SERVICE_FILESTREAMING_FLAG_MAPTOMEMORY = 4
    }

    public class CeateStreamResult
    {
        public CeateStreamResult(IAimpVirtualFile virtualFile, IAimpStream stream)
        {
            VirtualFile = virtualFile;
            Stream = stream;
        }

        public IAimpVirtualFile VirtualFile { get; }

        public IAimpStream Stream { get; }
    }

    public interface IAimpServiceFileStreaming : IAimpService
    {
        AimpActionResult<IAimpStream> CreateStreamForFile(string fileName, FileStreamingType flags, long offset, long size);

        AimpActionResult<CeateStreamResult> CreateStreamForFileUri(string fileUrl);
    }
}