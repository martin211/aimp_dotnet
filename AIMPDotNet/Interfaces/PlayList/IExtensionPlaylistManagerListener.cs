using System;

namespace AIMP.SDK.Services.PlayListManager
{
    public interface IExtensionPlaylistManagerListener
    {
        event EventHandler<PlayListEventArgs> PlaylistActivated;

        event EventHandler<PlayListEventArgs> PlaylistAdded;

        event EventHandler<PlayListEventArgs> PlaylistRemoved;
    }
}