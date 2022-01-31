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

using System.IO;
using AIMP.SDK;
using AIMP.SDK.FileManager;
using AIMP.SDK.FileManager.Extensions;
using AIMP.SDK.FileManager.Objects;
using AIMP.SDK.Objects;

namespace AIMP.DotNet.MusicLibrary
{
    public class MyExtensionFileInfoProvider : IAimpExtensionFileInfoProvider, IAimpExtension
    {
        private readonly IAimpPlayer _player;

        public MyExtensionFileInfoProvider(IAimpPlayer player)
        {
            _player = player;
        }

        //public ActionResultType GetFileInfo(string fileUri, ref IAimpFileInfo fileInfo)
        //{
        //    fileInfo.Artist = "test";
        //    //fileInfo = null;
        //    return ActionResultType.OK;
        //}

        public AimpActionResult GetFileInfo(string fileUri, ref IAimpFileInfo fileInfo)
        {
            fileInfo.Artist = "test";
            //fileInfo = null;
            return new AimpActionResult(ActionResultType.OK);
        }

        public AimpActionResult GetFileInfo(IAimpStream stream, ref IAimpFileInfo fileInfo)
        {
            return new AimpActionResult(ActionResultType.OK);
        }

        public ActionResultType GetFileInfo(Stream stream, ref IAimpFileInfo fileInfo)
        {
            //fileInfo = null;
            return ActionResultType.OK;
        }
    }
}
