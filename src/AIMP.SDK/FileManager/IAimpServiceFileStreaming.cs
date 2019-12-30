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

    public interface IAimpServiceFileStreaming : IAimpService
    {
        AimpActionResult CreateStreamForFile(string fileName, FileStreamingType flags, long offset, long size,
            out IAimpStream stream);

        AimpActionResult CreateStreamForFileUri(string fileUrl, out IAimpVirtualFile virtualFile,
            out IAimpStream stream);
    }
}