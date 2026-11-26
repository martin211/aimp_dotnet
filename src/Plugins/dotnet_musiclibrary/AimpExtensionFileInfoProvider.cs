using AIMP.SDK;
using AIMP.SDK.FileManager.Extensions;
using AIMP.SDK.FileManager.Objects;
using AIMP.SDK.Objects;

namespace Aimp.MusicLibraryPlugin
{
    public class AimpExtensionFileInfoProvider : IAimpExtensionFileInfoProvider, IAimpExtension
    {
        public AimpActionResult GetFileInfo(string fileUri, ref IAimpFileInfo fileInfo)
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
