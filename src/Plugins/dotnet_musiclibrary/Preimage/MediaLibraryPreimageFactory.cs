using System.Collections.Generic;
using AIMP.SDK;
using AIMP.SDK.PlayList.Extensions;
using AIMP.SDK.PlayList.Objects;

namespace Aimp.MusicLibraryPlugin.Preimage
{
    public class MediaLibraryPreimageFactory : IAimpExtensionPlaylistPreimageFactory, IAimpExtension
    {
        public MediaLibraryPreimageFactory()
        {
            Preimages = new List<IAimpPlaylistPreimage>();
        }

        public IList<IAimpPlaylistPreimage> Preimages { get; set; }

        public AimpActionResult<IAimpPlaylistPreimage> CreatePreimage()
        {
            return new AimpActionResult<IAimpPlaylistPreimage>(ActionResultType.OK, new TestMediaLibraryPreimage(this));
        }

        public AimpActionResult<string> GetId()
        {
            return new AimpActionResult<string>(ActionResultType.OK, nameof(MediaLibraryPreimageFactory));
        }

        public AimpActionResult<string> GetName()
        {
            return new AimpActionResult<string>(ActionResultType.OK, "Media library Test Preimage");
        }

        public PreimageFactoryFlags GetFlags()
        {
            return PreimageFactoryFlags.None;
        }
    }
}
