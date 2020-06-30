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
        public ActionResultType GetFileInfo(IAimpString fileUri, ref IAimpFileInfo fileInfo)
        {
            fileInfo = null;
            System.Diagnostics.Debugger.Break();
            return ActionResultType.OK;
        }

        public ActionResultType GetFileInfo(IAimpStream stream, ref IAimpFileInfo fileInfo)
        {
            fileInfo = null;
            System.Diagnostics.Debugger.Break();
            return ActionResultType.OK;
        }
    }
}