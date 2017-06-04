// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using AIMP.SDK;
using AIMP.SDK.Playlist;

namespace AIMP.DotNet.MusicLibrary.SmartPlaylist
{
    public class DemoSmartPlaylistsFactory : IAimpExtensionPlaylistPreimageFactory
    {
        public AimpActionResult CreatePreimage(out IAimpPlaylistPreimage preimage)
        {
            throw new System.NotImplementedException();
        }

        public AimpActionResult GetId(out string id)
        {
            throw new System.NotImplementedException();
        }

        public AimpActionResult GetName(out string name)
        {
            throw new System.NotImplementedException();
        }

        public int GetFlags()
        {
            throw new System.NotImplementedException();
        }
    }
}