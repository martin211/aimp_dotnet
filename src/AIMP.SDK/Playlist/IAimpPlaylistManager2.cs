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
    ///     Interface IAimpPlaylistManager2
    ///     Implements the <see cref="AIMP.SDK.Playlist.IAimpPlaylistManager" />
    ///     Implements the <see cref="AIMP.SDK.IAimpService" />
    /// </summary>
    /// <seealso cref="AIMP.SDK.Playlist.IAimpPlaylistManager" />
    /// <seealso cref="AIMP.SDK.IAimpService" />
    public interface IAimpPlaylistManager2 : IAimpPlaylistManager, IAimpService
    {
        /// <summary>
        ///     Gets the preimage factory.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="factory">The <see cref="IAimpExtensionPlaylistPreimageFactory" /> factory.</param>
        /// <returns>ActionResultType.</returns>
        ActionResultType GetPreimageFactory(int index, out IAimpExtensionPlaylistPreimageFactory factory);

        /// <summary>
        ///     Gets the preimage factory by identifier.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <param name="factory">The <see cref="IAimpExtensionPlaylistPreimageFactory" /> factory.</param>
        /// <returns>ActionResultType.</returns>
        ActionResultType GetPreimageFactoryByID(string id, out IAimpExtensionPlaylistPreimageFactory factory);

        /// <summary>
        ///     Gets the preimage factory count.
        /// </summary>
        /// <returns>System.Int32.</returns>
        int GetPreimageFactoryCount();
    }
}