namespace AIMP.SDK.MusicLibrary.Extension.Command
{
    public interface IAimpDataStorageCommandDeleteFiles
    {
        bool CanDelete(bool physically);

        AimpActionResult Delete(IAimpFileList files, bool physically);
    }
}