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

namespace AIMP.SDK.Playlist
{
    public enum PreimageFactoryFlags
    {
        AIMP_PREIMAGEFACTORY_FLAG_CONTEXTDEPENDENT = 1
    }

    /// <summary>
    /// Provides an ability to register custom preimage (data provider) factory for smart-playlists.
    /// </summary>
    public interface IAimpExtensionPlaylistPreimageFactory
    {
        /// <summary>
        /// Creates a new instance of <see cref="IAimpPlaylistPreimage"/>.
        /// </summary>
        /// <param name="preimage">The <see cref="IAimpPlaylistPreimage"/>.</param>
        /// <returns>The <see cref="AimpActionResult" /> result.</returns>
        AimpActionResult CreatePreimage(out IAimpPlaylistPreimage preimage);

        /// <summary>
        /// Unique ID of factory. You must not change the ID during life time of the plugin, because ID will be stored to file of smart-playlist.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <returns>The <see cref="AimpActionResult" /> result.</returns>
        AimpActionResult GetId(out string id);

        /// <summary>
        /// Gets the name.
        /// </summary>
        /// <param name="name">The name.</param>
        /// <returns>The <see cref="AimpActionResult" /> result.</returns>
        AimpActionResult GetName(out string name);

        PreimageFactoryFlags GetFlags();

        //string Name { get; }

        //string Id { get; }

        //PreimageFactoryFlags Flags { get; }
    }
}