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

using System;

namespace AIMP.SDK.FileManager.Commands
{
    public interface IAimpFileSystemCommandFileInfo : IAimpFileSystemCommand
    {
        AimpActionResult GetFileAttrs(IntPtr fileName, out AimpFileAttributes attr);

        AimpActionResult GetFileSize(string file, out long size);

        AimpActionResult IsFileExists(string file);
    }
}