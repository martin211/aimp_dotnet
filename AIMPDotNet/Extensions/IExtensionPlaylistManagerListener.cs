using System;

namespace AIMP.SDK.Extensions
{
    public interface IExtensionPlaylistManagerListener
    {
        event EventHandler PlaylistActivated;

        event EventHandler PlaylistAdded;

        event EventHandler PlaylistRemoved;
    }
}