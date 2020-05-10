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
using AIMP.SDK.Objects;

namespace AIMP.SDK.FileManager.Commands
{
    public interface IAimpFileSystemCommandDropSource : IAimpFileSystemCommand
    {
        /// <summary>
        /// 
        /// </summary>
        /// <param name="fileName"></param>
        AimpActionResult<IAimpStream> CreateStream(string fileName);
    }
}