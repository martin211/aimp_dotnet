//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System.Collections.Generic;
using AIMP.SDK;
using AIMP.SDK.Playlist;
using AIMP.SDK.Playlist.Extensions;
using AIMP.SDK.Playlist.Objects;

namespace AIMP.DotNet.MusicLibrary.Preimage
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
