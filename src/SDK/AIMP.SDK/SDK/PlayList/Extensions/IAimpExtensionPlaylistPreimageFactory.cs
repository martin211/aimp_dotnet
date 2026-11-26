using AIMP.SDK.PlayList.Objects;

namespace AIMP.SDK.PlayList.Extensions;

/// <summary>
/// Provides an ability to register custom preimage (data provider) factory for smart-playlists.
/// </summary>
public interface IAimpExtensionPlaylistPreimageFactory
{
    /// <summary>
    /// Creates a new instance of <see cref="IAimpPlaylistPreimage" />.
    /// </summary>
    /// <returns>AimpActionResult&lt;IAimpPlaylistPreimage&gt;.</returns>
    AimpActionResult<IAimpPlaylistPreimage> CreatePreimage();

    /// <summary>
    /// Unique ID of factory. You must not change the ID during life time of the plugin, because ID will be stored to file
    /// of smart-playlist.
    /// </summary>
    /// <returns>AimpActionResult&lt;System.String&gt;.</returns>
    AimpActionResult<string> GetId();

    /// <summary>
    /// Gets the name.
    /// </summary>
    /// <returns>AimpActionResult&lt;System.String&gt;.</returns>
    AimpActionResult<string> GetName();

    /// <summary>
    /// Gets the flags.
    /// </summary>
    /// <returns>PreimageFactoryFlags.</returns>
    PreimageFactoryFlags GetFlags();

    //string Name { get; }

    //string Id { get; }

    //PreimageFactoryFlags Flags { get; }
}