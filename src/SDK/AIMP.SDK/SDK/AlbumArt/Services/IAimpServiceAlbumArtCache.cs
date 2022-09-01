//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;
using AIMP.SDK.Objects;

namespace AIMP.SDK.AlbumArt.Services
{
    /// <summary>
    /// This service provides an access to cache manager for album arts.
    /// </summary>
    public interface IAimpServiceAlbumArtCache : IAimpService
    {
        /// <summary>
        /// Flushes cache for specified artist and album. Both parameters must be specified.
        /// </summary>
        /// <returns>ActionResultType.</returns>
        AimpActionResult Flush();

        /// <summary>
        /// Gets the image container for key.
        /// </summary>
        /// <param name="key">The key.</param>
        /// <returns>AimpActionResult&lt;IAimpImageContainer&gt;.</returns>
        AimpActionResult<IAimpImageContainer> Get(string key);

        /// <summary>
        /// Puts the specified image to cache.
        /// </summary>
        /// <param name="key">The key.</param>
        /// <param name="image">The image.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Put(string key, IAimpImageContainer image);

        /// <summary>
        /// Removes cache for the specified key.
        /// </summary>
        /// <param name="key">The key.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Remove(string key);

        /// <summary>
        /// Gets the cache stats.
        /// </summary>
        /// <returns>AimpActionResult&lt;Tuple&lt;System.Int32, System.Int32&gt;&gt;.</returns>
        AimpActionResult<Tuple<int, int>> Stat();
    }
}
