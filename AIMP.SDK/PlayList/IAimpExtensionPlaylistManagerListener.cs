namespace AIMP.SDK.PlayList
{
    public delegate void PlayListHandler(string playListName, string playListId);

    public interface IAimpExtensionPlaylistManagerListener
    {
        event PlayListHandler PlaylistActivated;

        event PlayListHandler PlaylistAdded;
        
        event PlayListHandler PlaylistRemoved;
    }
}