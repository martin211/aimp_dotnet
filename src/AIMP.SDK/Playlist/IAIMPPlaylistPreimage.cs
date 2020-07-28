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

using System;

namespace AIMP.SDK.Playlist
{
    /// <summary>
    ///     It is a general interface for all preimages.
    ///     <para>
    ///         Preimage is data source for smart-playlists with manual or automatic synchronization.
    ///         The principle of cooperation between preimage and playlist is so simple: when data or settings in preimage are
    ///         changed - preimage notify playlist about the changes via the <see cref="IAimpPlaylistPreimageListener" />
    ///         interface that related to binded playlist.
    ///         Playlist, in own case, will reload data from preimage as soon as data will be required by plugin or user.
    ///     </para>
    /// </summary>
    public interface IAimpPlaylistPreimage
    {
        /// <summary>
        ///     Id of factory that creates this preimage.
        /// </summary>
        /// <value>The factory identifier.</value>
        string FactoryId { get; }

        /// <summary>
        ///     The Value different from false if automatic synchronization is switched on in the preimage (note that not all
        ///     preimages support for this property).
        /// </summary>
        /// <value><c>true</c> if [automatic synchronize]; otherwise, <c>false</c>.</value>
        bool AutoSync { get; set; }

        /// <summary>
        ///     The Value different from false if automatic synchronization is switched on in the preimage at Application startup
        ///     (note that not all preimages support for this property).
        /// </summary>
        /// <value><c>true</c> if [automatic synchronize on startup]; otherwise, <c>false</c>.</value>
        bool AutoSyncOnStartup { get; set; }

        /// <summary>
        ///     Return value different from false if preimage has implementation of the ExecuteDialog method.
        /// </summary>
        /// <value><c>true</c> if this instance has dialog; otherwise, <c>false</c>.</value>
        bool HasDialog { get; }

        /// <summary>
        ///     Return sorting template for values in playlist after adding files from preimage.
        /// </summary>
        /// <value>The sort template.</value>
        string SortTemplate { get; }

        /// <summary>
        ///     Loads the configuration.
        /// </summary>
        /// <param name="stream">The stream.</param>
        /// <returns>Operation result <seealso cref="ActionResultType" /></returns>
        ActionResultType ConfigLoad(IAimpStream stream);

        /// <summary>
        ///     Saves the configuration.
        /// </summary>
        /// <param name="stream">The stream.</param>
        /// <returns>Operation result <seealso cref="ActionResultType" /></returns>
        ActionResultType ConfigSave(IAimpStream stream);

        /// <summary>
        ///     Executes the dialog.
        /// </summary>
        /// <param name="ownerHandle">The owner handle.</param>
        /// <returns>ActionResultType.</returns>
        ActionResultType ExecuteDialog(IntPtr ownerHandle);

        /// <summary>
        ///     Initializes the specified listener.
        /// </summary>
        /// <param name="listener">The listener.</param>
        void Initialize(IAimpPlaylistPreimageListener listener);

        /// <summary>
        ///     Finalizes the object.
        /// </summary>
        void FinalizeObject();
    }
}