namespace AIMP.SDK.Services.PlayList
{
    using AIMP.SDK.Extensions;

    public interface IAimpPlayListManager : IExtensionPlaylistManagerListener
    {
        IAimpPlayList CreatePlaylist(string name, bool isActive);

        IAimpPlayList CreatePlaylistFromFile(string fileName, bool isActive);

        IAimpPlayList GetActivePlaylist();

        void SetActivePlaylist(IAimpPlayList playList);

        IAimpPlayList GetPlayablePlaylist();

        IAimpPlayList GetLoadedPlaylist(int index);

        IAimpPlayList GetLoadedPlaylistById(string id);

        IAimpPlayList GetLoadedPlaylistByName(string name);

        int GetLoadedPlaylistCount();
    }
}