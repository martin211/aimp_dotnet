using AIMP.SDK.PlayList.Extensions;

namespace AIMP.SDK.PlayList;

/// <summary>
/// Interface IAimpPlaylistManager2
/// </summary>
public interface IAimpServicePlaylistManager2
{
    /// <summary>
    /// Gets the preimage factory.
    /// </summary>
    /// <param name="index">The index.</param>
    /// <returns>ActionResultType.</returns>
    AimpActionResult<IAimpExtensionPlaylistPreimageFactory> GetPreimageFactory(int index);

    /// <summary>
    /// Gets the preimage factory by identifier.
    /// </summary>
    /// <param name="id">The identifier.</param>
    /// <returns>ActionResultType.</returns>
    AimpActionResult<IAimpExtensionPlaylistPreimageFactory> GetPreimageFactoryById(string id);

    /// <summary>
    /// Gets the preimage factory count.
    /// </summary>
    /// <returns>System.Int32.</returns>
    int GetPreimageFactoryCount();
}