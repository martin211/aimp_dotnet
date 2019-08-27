// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------
using AIMP.SDK;
using AIMP.SDK.Playlist;

namespace AIMP.DotNet.MusicLibrary.Preimage
{
    public class PlaylistManagerListener : IAimpExtensionPlaylistManagerListener, IAimpExtension
    {
        public AimpActionResult OnPlaylistActivated(IAimpPlaylist playlist)
        {
            return AimpActionResult.Ok;
        }

        public AimpActionResult OnPlaylistAdded(IAimpPlaylist playlist)
        {
            return AimpActionResult.Ok;
        }

        public AimpActionResult OnPlaylistRemoved(IAimpPlaylist playlist)
        {
            return AimpActionResult.Ok;
        }
    }
}