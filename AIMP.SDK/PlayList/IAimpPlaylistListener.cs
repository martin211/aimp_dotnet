namespace AIMP.SDK.PlayList
{
    public delegate void PlayListChangedHandler(IAimpPlayList sender, PlayListNotifyType notifType);

    public delegate void AimpPlayListHandler(IAimpPlayList sender);

    public interface IAimpPlaylistListener
    {
        event AimpPlayListHandler Activated;

        event AimpPlayListHandler Removed;

        event PlayListChangedHandler Changed;
    }
}