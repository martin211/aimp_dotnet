﻿// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

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
        /// <param name="album">The album.</param>
        /// <param name="artist">The artist.</param>
        /// <returns>ActionResultType.</returns>
        AimpActionResult Flush(string album, string artist);

        /// <summary>
        /// Flushes cache for specified FileURI. FileURI can include wildcard characters, for example, an asterisk (*) or a
        /// question mark (?).
        /// </summary>
        /// <param name="fileUri">The file URI.</param>
        /// <returns>ActionResultType.</returns>
        AimpActionResult Flush2(string fileUri);

        /// <summary>
        /// Flushes all cache.
        /// </summary>
        /// <returns>ActionResultType.</returns>
        AimpActionResult FlushAll();
    }
}
