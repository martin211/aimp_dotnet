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

using System.Collections.Generic;

namespace AIMP.SDK.FileManager.Commands
{
    public interface IAimpFileSystemCommandCopyToClipboard : IAimpFileSystemCommand
    {
        AimpActionResult CopyToClipboard(List<string> files);
    }
}