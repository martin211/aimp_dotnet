namespace AIMP.SDK.AlbumArtManager
{
    /// <summary>
    /// This service provides an access to cache manager for album arts.
    /// </summary>
    public interface IAimpServiceAlbumArtCache
    {
        /// <summary>
        /// Flushes cache for specified artist and album. Both parameters must be specified.
        /// </summary>
        /// <param name="album">The album.</param>
        /// <param name="artist">The artist.</param>
        /// <returns>ActionResultType.</returns>
        AimpActionResult Flush(string album, string artist);

        /// <summary>
        /// Flushes cache for specified FileURI. FileURI can include wildcard characters, for example, an asterisk (*) or a question mark (?). 
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