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

namespace AIMP.SDK.FileManager.Commands
{
    public interface IAimpFileSystemCommandFileInfo : IAimpFileSystemCommand
    {
        AimpActionResult GetFileAttrs(string file, out AimpFileAttributes attr);

        AimpActionResult GetFileSize(string file, out long size);

        AimpActionResult IsFileExists(string file);
    }
}