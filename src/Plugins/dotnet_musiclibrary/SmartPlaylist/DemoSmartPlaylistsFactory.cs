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

using System;
using AIMP.SDK;
using AIMP.SDK.Playlist;
using AIMP.SDK.Threading;

namespace AIMP.DotNet.MusicLibrary.SmartPlaylist
{
    public class DemoSmartPlaylistsFactory : IAimpExtensionPlaylistPreimageFactory, IAimpPlaylistPreimageDataProvider, IAimpExtension
    {

        public AimpActionResult CreatePreimage(out IAimpPlaylistPreimage preimage)
        {
            preimage = new DemoSmartPlaylist();
            return AimpActionResult.Ok;
        }

        public AimpActionResult GetId(out string id)
        {
            id = "DemoFactory";
            return AimpActionResult.Ok;
        }

        public AimpActionResult GetName(out string name)
        {
            name = "DemoFactory";
            return AimpActionResult.Ok;
        }

        PreimageFactoryFlags IAimpExtensionPlaylistPreimageFactory.GetFlags()
        {
            return PreimageFactoryFlags.AIMP_PREIMAGEFACTORY_FLAG_CONTEXTDEPENDENT;
        }

        public AimpActionResult GetFiles(IAimpTaskOwner owner, PreimageFlags preimageFlags, IAimpObjectList<object> dataList)
        {
            throw new NotImplementedException();
        }
    }
}