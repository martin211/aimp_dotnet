using AIMP.SDK;
using AIMP.SDK.FileManager.Extensions;
using AIMP.SDK.Objects;

namespace Aimp.MusicLibraryPlugin
{
    public class
        DemoExtensionFileSystem : IAimpExtensionFileSystem, IAimpExtension //, IAimpFileSystemCommandOpenFileFolder
    {
        public string Schema => "myschema";

        public bool ReadOnly => false;

        public ActionResultType CreateStream(string file, out IAimpStream stream)
        {
            stream = null;
            return ActionResultType.NotImplemented;
        }

        public ActionResultType CanProcess(string file)
        {
            return ActionResultType.OK;
        }

        public ActionResultType Process(string file)
        {
            return ActionResultType.OK;
        }
    }
}
