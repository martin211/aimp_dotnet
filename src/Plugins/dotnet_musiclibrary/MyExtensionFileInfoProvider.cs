using System.IO;
using AIMP.SDK;
using AIMP.SDK.FileManager;
using AIMP.SDK.FileManager.Extensions;
using AIMP.SDK.Objects;
using AIMP.SDK.Player;

namespace AIMP.DotNet.MusicLibrary
{
    public class MyExtensionFileInfoProvider : IAimpExtensionFileInfoProvider, IAimpExtension
    {
        private readonly IAimpPlayer _player;

        public MyExtensionFileInfoProvider(IAimpPlayer player)
        {
            _player = player;
        }

        //public AimpActionResult GetFileInfo(string fileUri, ref IAimpFileInfo fileInfo)
        //{
        //    fileInfo.Artist = "test";
        //    //fileInfo = null;
        //    return AimpActionResult.Ok;
        //}

        public AimpActionResult GetFileInfo(IAimpString fileUri, ref IAimpFileInfo fileInfo)
        {
            fileInfo.Artist = "test";
            //fileInfo = null;
            return AimpActionResult.Ok;
        }

        public AimpActionResult GetFileInfo(Stream stream, ref IAimpFileInfo fileInfo)
        {
            //fileInfo = null;
            return AimpActionResult.Ok;
        }
    }
}
