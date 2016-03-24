namespace AIMP.SDK.PlayList
{
    public interface IAimpPlayListManager : IAimpExtensionPlaylistManagerListener, IAimpExtension
    {
        IAimpPlayListQueue PlayListQueue { get; }

        AimpActionResult CreatePlaylist(string name, bool isActive, out IAimpPlayList playList);

        AimpActionResult CreatePlaylistFromFile(string fileName, bool isActive, out IAimpPlayList playList);

        AimpActionResult GetActivePlaylist(out IAimpPlayList playList);

        void SetActivePlaylist(IAimpPlayList playList);

        AimpActionResult GetPlayablePlaylist(out IAimpPlayList playList);

        AimpActionResult GetLoadedPlaylist(int index, out IAimpPlayList playList);

        AimpActionResult GetLoadedPlaylistById(string id, out IAimpPlayList playList);

        AimpActionResult GetLoadedPlaylistByName(string name, out IAimpPlayList playList);

        int GetLoadedPlaylistCount();
    }
}