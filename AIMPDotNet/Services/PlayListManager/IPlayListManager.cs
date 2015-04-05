namespace AIMP.SDK.Services.PlayListManager
{
    public interface IPlayListManager
    {
        void CreatePlaylist(string name, bool isActive);

        void CreatePlaylistFromFile(string fileName, bool isActive);
    }
}