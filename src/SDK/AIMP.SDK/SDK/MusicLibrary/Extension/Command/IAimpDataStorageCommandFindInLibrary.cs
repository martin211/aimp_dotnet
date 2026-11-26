using AIMP.SDK.FileManager.Objects;

namespace AIMP.SDK.MusicLibrary.Extension.Command;

public interface IAimpDataStorageCommandFindInLibrary
{
    AimpActionResult<FindResult> Find(IAimpFileInfo fileInfo);
}