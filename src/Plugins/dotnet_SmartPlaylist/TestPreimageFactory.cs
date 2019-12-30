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
using System.Collections.Generic;
using AIMP.SDK;
using AIMP.SDK.Playlist;

namespace Aimp.DotNet.SmartPlaylist
{
    public class TestPreimageFactory : IAimpExtensionPlaylistPreimageFactory, IAimpExtension
    {
        public TestPreimageFactory()
        {
            Preimages = new List<IAimpPlaylistPreimage>();
        }

        public IList<IAimpPlaylistPreimage> Preimages { get; set; }

        public AimpActionResult CreatePreimage(out IAimpPlaylistPreimage preimage)
        {
            preimage = new TestPreimage(this);
            return AimpActionResult.OK;
        }

        public AimpActionResult GetId(out string id)
        {
            id = nameof(TestPreimageFactory);
            return AimpActionResult.OK;
        }

        public AimpActionResult GetName(out string name)
        {
            name = "Test Preimage";
            return AimpActionResult.OK;
        }

        public PreimageFactoryFlags GetFlags()
        {
            return PreimageFactoryFlags.None;
        }
    }
}