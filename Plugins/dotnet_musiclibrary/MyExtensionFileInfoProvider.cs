using System.IO;
using AIMP.SDK;
using AIMP.SDK.FileManager;
using AIMP.SDK.FileManager.Extensions;

namespace AIMP.DotNet.MusicLibrary
{
    public class MyExtensionFileInfoProvider : IAimpExtensionFileInfoProvider, IAimpExtension
    {
        public AimpActionResult GetFileInfo(string fileUri, out IAimpFileInfo fileInfo)
        {
            System.Diagnostics.Debugger.Break();
            fileInfo = null;
            return AimpActionResult.Ok;
        }

        public AimpActionResult GetFileInfo(Stream stream, out IAimpFileInfo fileInfo)
        {
            System.Diagnostics.Debugger.Break();
            fileInfo = null;
            return AimpActionResult.Ok;
        }
    }
}
