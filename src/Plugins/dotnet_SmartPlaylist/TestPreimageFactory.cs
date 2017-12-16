using System.Collections.Generic;
using AIMP.SDK;
using AIMP.SDK.Playlist;

namespace Aimp.DotNet.SmartPlaylist
{
    public class TestPreimageFactory : IAimpExtensionPlaylistPreimageFactory, IAimpExtension
    {
        public IList<IAimpPlaylistPreimage> Preimages { get; set; }

        public TestPreimageFactory()
        {
            Preimages = new List<IAimpPlaylistPreimage>();
        }

        public AimpActionResult CreatePreimage(out IAimpPlaylistPreimage preimage)
        {
            preimage = new TestPreimage(this);
            return AimpActionResult.Ok;
        }

        public AimpActionResult GetId(out string id)
        {
            id = nameof(TestPreimageFactory);
            return AimpActionResult.Ok;
        }

        public AimpActionResult GetName(out string name)
        {
            name = "Test Preimage";
            return AimpActionResult.Ok;
        }

        public PreimageFactoryFlags GetFlags()
        {
            return PreimageFactoryFlags.None;
        }
    }
}