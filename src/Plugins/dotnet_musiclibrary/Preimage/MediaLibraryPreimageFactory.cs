using System.Collections.Generic;
using AIMP.SDK;
using AIMP.SDK.Playlist;

namespace AIMP.DotNet.MusicLibrary.Preimage
{
    public class MediaLibraryPreimageFactory : IAimpExtensionPlaylistPreimageFactory, IAimpExtension
    {
        public IList<IAimpPlaylistPreimage> Preimages { get; set; }

        public MediaLibraryPreimageFactory()
        {
            Preimages = new List<IAimpPlaylistPreimage>();
        }

        public AimpActionResult CreatePreimage(out IAimpPlaylistPreimage preimage)
        {
            preimage = new TestMediaLibraryPreimage(this);
            return AimpActionResult.Ok;
        }

        public AimpActionResult GetId(out string id)
        {
            id = nameof(MediaLibraryPreimageFactory);
            return AimpActionResult.Ok;
        }

        public AimpActionResult GetName(out string name)
        {
            name = "Media library Test Preimage";
            return AimpActionResult.Ok;
        }

        public PreimageFactoryFlags GetFlags()
        {
            return PreimageFactoryFlags.None;
        }
    }
}