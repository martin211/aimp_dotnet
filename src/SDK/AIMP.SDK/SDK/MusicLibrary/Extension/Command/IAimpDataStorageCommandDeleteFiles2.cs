namespace AIMP.SDK.MusicLibrary.Extension.Command;

public interface IAimpDataStorageCommandDeleteFiles2 : IAimpDataStorageCommandDeleteFiles
{
    AimpActionResult Delete2(IAimpDataFilter filter, bool physically);
}