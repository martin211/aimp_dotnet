using System.Collections.Generic;

namespace AIMP.SDK.MusicLibrary.Extension.Command
{
    public interface IAimpDataStorageCommandReloadTags
    {
        AimpActionResult ReloadTags(IAimpFileList files);
    }
}