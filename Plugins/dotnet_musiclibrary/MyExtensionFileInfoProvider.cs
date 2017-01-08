using System.IO;
using AIMP.SDK;
using AIMP.SDK.FileManager;
using AIMP.SDK.FileManager.Extensions;

namespace AIMP.DotNet.MusicLibrary
{
    public class MyExtensionFileInfoProvider : IAimpExtensionFileInfoProvider, IAimpExtension
    {
        public AimpActionResult GetFileInfo(string fileUri, ref IAimpFileInfo fileInfo)
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
