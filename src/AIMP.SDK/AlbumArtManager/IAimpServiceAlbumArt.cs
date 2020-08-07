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
using AIMP.SDK.FileManager;

namespace AIMP.SDK.AlbumArtManager
{
    /// <summary>
    /// Service provides an ability to get album art for specified file or/and album.
    /// AlbumArt search process will run in separate thread, and plugin will receive a notification about the end of
    /// operation via callback function.
    /// Implements the <see cref="AIMP.SDK.AlbumArtManager.IAimpAlbumArtSearchOptions" />
    /// Implements the <see cref="AIMP.SDK.IAimpService" />
    /// </summary>
    /// <seealso cref="AIMP.SDK.AlbumArtManager.IAimpAlbumArtSearchOptions" />
    /// <seealso cref="AIMP.SDK.IAimpService" />
    public interface IAimpServiceAlbumArt : IAimpAlbumArtSearchOptions, IAimpService
    {
        /// <summary>
        /// Occurs when search was completed.
        /// </summary>
        event EventHandler<AimpGetAlbumArtEventArgs> Completed;

        /// <summary>
        /// Gets the image.
        /// </summary>
        /// <param name="fileUrl">The file URL.</param>
        /// <param name="artist">Optional. The artist.</param>
        /// <param name="album">Optional. The album.</param>
        /// <param name="flags">Optional. The <see cref="AimpFindCovertArtType" />.</param>
        /// <param name="userData">The user data.</param>
        /// <returns>AimpActionResult&lt;System.Int32&gt;.</returns>
        AimpActionResult<int> Get(string fileUrl, string artist, string album, AimpFindCovertArtType flags,
            object userData);

        /// <summary>
        /// Gets the image.
        /// </summary>
        /// <param name="fileInfo">The file information.</param>
        /// <param name="flags">The flags.</param>
        /// <param name="userData">The user data.</param>
        /// <returns>AimpActionResult&lt;System.Int32&gt;.</returns>
        AimpActionResult<int> Get2(IAimpFileInfo fileInfo, AimpFindCovertArtType flags, object userData);

        /// <summary>
        /// Cancels the get cover art request by specified task identifier.
        /// </summary>
        /// <param name="taskId">The task identifier.</param>
        /// <param name="flags">The flags.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Cancel(int taskId, AimpFindCovertArtType flags);
    }
}
