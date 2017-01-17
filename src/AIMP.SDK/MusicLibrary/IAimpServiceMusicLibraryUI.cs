namespace AIMP.SDK.MusicLibrary
{
    public enum FilesType
    {
        All,
        Selected,
        Focused
    }

    public interface IAimpServiceMusicLibraryUI
    {
        AimpActionResult GetFiles(FilesType flags, out IAimpFileList list);

        AimpActionResult GetGroupingFilter(out IAimpDataFilter filter);

        AimpActionResult GetGroupingFilterPath(out string path);

        AimpActionResult SetGroupingFilterPath(string path);
    }
}