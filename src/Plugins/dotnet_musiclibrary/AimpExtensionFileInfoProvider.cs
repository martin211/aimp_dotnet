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
using System.IO;
using AIMP.SDK;
using AIMP.SDK.FileManager;
using AIMP.SDK.FileManager.Extensions;
using AIMP.SDK.Objects;

namespace AIMP.DotNet.MusicLibrary
{
    public class AimpExtensionFileInfoProvider : IAimpExtensionFileInfoProvider, IAimpExtension
    {
        //public AimpActionResult GetFileInfo(string fileUri, out IAimpFileInfo fileInfo)
        //{
        //    fileInfo = null;
        //    System.Diagnostics.Debugger.Break();
        //    return AimpActionResult.Ok;
        //}

        //public AimpActionResult GetFileInfo(Stream stream, out IAimpFileInfo fileInfo)
        //{
        //    fileInfo = null;
        //    System.Diagnostics.Debugger.Break();
        //    return AimpActionResult.Ok;
        //}

        public AimpActionResult GetFileInfo(IAimpString fileUri, ref IAimpFileInfo fileInfo)
        {
            fileInfo = null;
            System.Diagnostics.Debugger.Break();
            return AimpActionResult.Ok;
        }

        public AimpActionResult GetFileInfo(Stream stream, ref IAimpFileInfo fileInfo)
        {
            fileInfo = null;
            System.Diagnostics.Debugger.Break();
            return AimpActionResult.Ok;
        }
    }
}