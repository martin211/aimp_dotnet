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

        public ActionResultType CreatePreimage(out IAimpPlaylistPreimage preimage)
        {
            preimage = new TestPreimage(this);
            return ActionResultType.OK;
        }

        public ActionResultType GetId(out string id)
        {
            id = nameof(TestPreimageFactory);
            return ActionResultType.OK;
        }

        public ActionResultType GetName(out string name)
        {
            name = "Test Preimage";
            return ActionResultType.OK;
        }

        public PreimageFactoryFlags GetFlags()
        {
            return PreimageFactoryFlags.None;
        }
    }
}