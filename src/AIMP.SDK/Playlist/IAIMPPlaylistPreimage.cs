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

using System;

namespace AIMP.SDK.Playlist
{
    /// <summary>
    /// It is a general interface for all preimages.
    /// <para>
    /// Preimage is data source for smart-playlists with manual or automatic synchronization.
    /// The principle of cooperation between preimage and playlist is so simple: when data or settings in preimage are changed - preimage notify playlist about the changes via the <see cref="IAimpPlaylistPreimageListener"/> interface that related to binded playlist. Playlist, in own case, will reload data from preimage as soon as data will be required by plugin or user.
    /// </para>
    /// </summary>
    public interface IAimpPlaylistPreimage : IAimpPlaylistPreimageListener
    {
        /// <summary>
        /// Id of factory that creates this preimage.
        /// </summary>
        string FactoryId { get; }

        /// <summary>
        /// The Value different from false if automatic synchronization is switched on in the preimage (note that not all preimages support for this property).
        /// </summary>
        bool AutoSync { get; set; }

        /// <summary>
        /// The Value different from false if automatic synchronization is switched on in the preimage at Application startup (note that not all preimages support for this property).
        /// </summary>
        bool AutoSyncOnStartup { get; set; }

        /// <summary>
        /// Return value different from false if preimage has implementation of the ExecuteDialog method.
        /// </summary>
        bool HasDialog { get; }

        /// <summary>
        /// Return sorting template for values in playlist after adding files from preimage.
        /// </summary>
        string SortTemplate { get; }

        /// <summary>
        /// Loads the configuration.
        /// </summary>
        /// <param name="stream">The stream.</param>
        /// <returns>The <see cref="AimpActionResult"/> result.</returns>
        AimpActionResult ConfigLoad(IAimpStream stream);

        /// <summary>
        /// Saves the configuration.
        /// </summary>
        /// <param name="stream">The stream.</param>
        /// <returns>The <see cref="AimpActionResult"/> result.</returns>
        AimpActionResult ConfigSave(IAimpStream stream);

        AimpActionResult ExecuteDialog(IntPtr ownerHandle);
    }
}