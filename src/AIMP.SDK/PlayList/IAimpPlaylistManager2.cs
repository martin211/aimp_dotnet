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
    public interface IAimpPlaylistManager2 : IAimpPlaylistManager
    {
        /// <summary>
        /// Gets the preimage factory.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="factory">The <see cref="IAimpExtensionPlaylistPreimageFactory" /> factory.</param>
        /// <returns></returns>
        AimpActionResult GetPreimageFactory(int index, out IAimpExtensionPlaylistPreimageFactory factory);

        /// <summary>
        /// Gets the preimage factory by identifier.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <param name="factory">The <see cref="IAimpExtensionPlaylistPreimageFactory"/> factory.</param>
        /// <returns></returns>
        AimpActionResult GetPreimageFactoryByID(string id, out IAimpExtensionPlaylistPreimageFactory factory);

        int GetPreimageFactoryCount();
    }
}