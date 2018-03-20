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
using System.IO;

namespace AIMP.SDK.FileManager.Commands
{
    public interface IAimpFileSystemCommandDropSource : IAimpFileSystemCommand
    {
        /// <summary>
        /// 
        /// </summary>
        /// <param name="fileName"></param>
        IAimpStream CreateStream(IntPtr fileNameHeader);
    }
}