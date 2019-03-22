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

namespace AIMP.DotNet.MusicLibrary.Preimage
{
    public class MediaLibraryPreimageFactory : IAimpExtensionPlaylistPreimageFactory, IAimpExtension
    {
        public MediaLibraryPreimageFactory()
        {
            Preimages = new List<IAimpPlaylistPreimage>();
        }

        public IList<IAimpPlaylistPreimage> Preimages { get; set; }

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