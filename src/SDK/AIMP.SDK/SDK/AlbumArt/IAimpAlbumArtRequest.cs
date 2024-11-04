//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System.Drawing;
using AIMP.SDK.Objects;

namespace AIMP.SDK.AlbumArt;

/// <summary>
/// The search options for album art.
/// </summary>
public interface IAimpAlbumArtRequest
{
    /// <summary>
    /// Gets or sets a value indicating whether allow an ability to find album art in files.
    /// </summary>
    /// <value><c>true</c> if [find in files]; otherwise, <c>false</c>.</value>
    bool FindInFiles { get; set; }

    /// <summary>
    /// Gets or sets the file masks for searching.
    /// <para>
    /// List of templates (without extensions) for searching.
    /// Each value must be separated from others via ";".
    /// </para>
    /// </summary>
    /// <value>The file masks.</value>
    string[] FindInFileMasks { get; set; }

    /// <summary>
    /// Gets or sets the available cover file extensions.
    /// <para>
    /// List of extensions that are supported.
    /// Each value must be separated from others via ";".
    /// </para>
    /// </summary>
    /// <value>The file extensions.</value>
    string[] FindInFileExtensions { get; set; }

    /// <summary>
    /// Gets or sets a value indicating whether allow an ability to find album art in internet.
    /// </summary>
    /// <value><c>true</c> if [find in internet]; otherwise, <c>false</c>.</value>
    bool FindInInternet { get; set; }

    /// <summary>
    /// Gets or sets the maximum size of the file which can be downloaded from internet.
    /// 0 - size is unlimited.
    /// </summary>
    int FindInInternetMaxFileSize { get; set; }

    /// <summary>
    /// Gets or sets a value indicating whether allow an ability to find album art in file tags.
    /// </summary>
    bool FindInTags { get; set; }

    /// <summary>
    /// Get image from cache.
    /// </summary>
    /// <param name="key"></param>
    /// <returns></returns>
    AimpActionResult<IAimpImageContainer> CacheGet(string key);

    /// <summary>
    /// Caches the get as bitmap.
    /// </summary>
    /// <param name="key">The key.</param>
    AimpActionResult<Bitmap> CacheGetAsBitmap(string key);

    /// <summary>
    /// Put image to cache.
    /// </summary>
    /// <param name="key">The key.</param>
    /// <param name="image">The image.</param>
    AimpActionResult CachePut(string key, IAimpImageContainer image);

    /// <summary>
    /// Downloads the specified file by URL.
    /// </summary>
    /// <param name="url">The file URL.</param>
    AimpActionResult<IAimpImageContainer> Download(string url);

    /// <summary>
    /// Is request canceled.
    /// </summary>
    bool IsCanceled();
}
