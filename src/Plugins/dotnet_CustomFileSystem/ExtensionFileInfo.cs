using System.IO;
using AIMP.SDK.FileManager;
using AIMP.SDK.FileManager.Extensions;
using AIMP.SDK.Objects;

namespace AIMP.SDK.CustomFileSystem
{
    public class ExtensionFileInfo : IAimpExtension, IAimpExtensionFileInfoProvider
    {
        public AimpActionResult GetFileInfo(IAimpString fileUri, ref IAimpFileInfo fileInfo)
        {
            var file = fileUri.GetData().Replace(CustomFileSystem.sMySchemePrefix, string.Empty);
            if (File.Exists(file))
            {
                fileInfo.Album = "test";
            }

            return AimpActionResult.Ok;
        }

        public AimpActionResult GetFileInfo(Stream stream, ref IAimpFileInfo fileInfo)
        {
            throw new System.NotImplementedException();
        }
    }
}