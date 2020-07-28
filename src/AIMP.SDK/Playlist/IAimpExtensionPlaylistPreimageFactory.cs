// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

namespace AIMP.SDK.Playlist
{
    public enum PreimageFactoryFlags
    {
        None = 0,
        ContextDependent = 1
    }

    /// <summary>
    /// Provides an ability to register custom preimage (data provider) factory for smart-playlists.
    /// </summary>
    public interface IAimpExtensionPlaylistPreimageFactory
    {
        /// <summary>
        /// Creates a new instance of <see cref="IAimpPlaylistPreimage"/>.
        /// </summary>
        AimpActionResult<IAimpPlaylistPreimage> CreatePreimage();

        /// <summary>
        /// Unique ID of factory. You must not change the ID during life time of the plugin, because ID will be stored to file of smart-playlist.
        /// </summary>
        AimpActionResult<string> GetId();

        /// <summary>
        /// Gets the name.
        /// </summary>
        AimpActionResult<string> GetName();

        PreimageFactoryFlags GetFlags();

        //string Name { get; }

        //string Id { get; }

        //PreimageFactoryFlags Flags { get; }
    }
}