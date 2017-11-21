namespace AIMP.SDK.Playlist
{
    public interface IAimpPlaylistPreimageFolders : IAimpPlaylistPreimage
    {
        AimpActionResult ItemsAdd(string path, bool recursive);

        AimpActionResult ItemsDelete(int index);

        AimpActionResult ItemsDeleteAll();

        AimpActionResult ItemsGet(int index, out string path, out bool recursive);

        int ItemsGetCount();
    }
}