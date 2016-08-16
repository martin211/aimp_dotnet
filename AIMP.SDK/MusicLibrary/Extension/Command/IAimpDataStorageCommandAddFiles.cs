using System.Collections.Generic;

namespace AIMP.SDK.MusicLibrary.Extension.Command
{
    public interface IAimpDataStorageCommandAddFiles
    {
        AimpActionResult Add(IList<string> files);
    }
}