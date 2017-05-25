// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

namespace AIMP.SDK.FileManager
{
    public enum FileStreamingType
    {
        AIMP_SERVICE_FILESTREAMING_FLAG_CREATENEW = 1,
        AIMP_SERVICE_FILESTREAMING_FLAG_READ = 2,
        AIMP_SERVICE_FILESTREAMING_FLAG_READWRITE = 3,
        AIMP_SERVICE_FILESTREAMING_FLAG_MAPTOMEMORY = 4
    }

    public interface IAimpServiceFileStreaming
    {
        AimpActionResult CreateStreamForFile(string fileName, FileStreamingType flags, long ofset, long size,
            out IAimpStream stream);

        AimpActionResult CreateStreamForFileUri(string fileUrl, out IAimpVirtualFile virtualFile,
            out IAimpStream stream);
    }
}