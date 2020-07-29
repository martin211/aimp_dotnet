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

using AIMP.SDK;
using AIMP.SDK.FileManager;
using AIMP.SDK.FileManager.Extensions;
using AIMP.SDK.Objects;

namespace AIMP.DotNet.MusicLibrary
{
    public class AimpExtensionFileInfoProvider : IAimpExtensionFileInfoProvider, IAimpExtension
    {
        public AimpActionResult GetFileInfo(IAimpString fileUri, ref IAimpFileInfo fileInfo)
        {
            fileInfo = null;
            System.Diagnostics.Debugger.Break();
            return new AimpActionResult(ActionResultType.OK);
        }

        public AimpActionResult GetFileInfo(IAimpStream stream, ref IAimpFileInfo fileInfo)
        {
            fileInfo = null;
            System.Diagnostics.Debugger.Break();
            return new AimpActionResult(ActionResultType.OK);
        }
    }
}