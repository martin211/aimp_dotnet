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
    /// <summary>
    /// Interface IAimpPlaylistManager2
    /// </summary>
    public interface IAimpPlaylistManager2
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
}