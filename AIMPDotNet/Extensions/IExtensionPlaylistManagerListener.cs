namespace AIMP.SDK.Extensions
{
    public delegate void PlayListHandler(string playListName, string playListId);

    public interface IExtensionPlaylistManagerListener
    {
        event PlayListHandler PlaylistActivated;

        event PlayListHandler PlaylistAdded;
        
        event PlayListHandler PlaylistRemoved;
    }
}