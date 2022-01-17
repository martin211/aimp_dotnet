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

using System.Drawing;

namespace AIMP.SDK.AlbumArt.Extensions
{
    /// <summary>
    /// Enum AimpAlbumArtProviderCategory
    /// </summary>
    public enum AimpAlbumArtProviderCategory
    {
        /// <summary>
        /// The aimp albumart provider category tags
        /// </summary>
        AIMP_ALBUMART_PROVIDER_CATEGORY_TAGS,

        /// <summary>
        /// The aimp albumart provider category file
        /// </summary>
        AIMP_ALBUMART_PROVIDER_CATEGORY_FILE,

        /// <summary>
        /// The aimp albumart provider category internet
        /// </summary>
        AIMP_ALBUMART_PROVIDER_CATEGORY_INTERNET
    }

    /// <summary>
    /// Interface allows for the plugin to register custom album art provider.
    /// </summary>
    /// <seealso cref="IAimpExtensionAlbumArtProvider2" />
    /// <seealso cref="AIMP.SDK.IAimpExtension" />
    public interface IAimpExtensionAlbumArtProvider : IAimpExtensionAlbumArtProvider2, IAimpExtension
    {
        /// <summary>
        /// Gets the album art image.
        /// </summary>
        /// <param name="fileUrl">The file URL.</param>
        /// <param name="artist">Optional. The artist.</param>
        /// <param name="album">Optional.The album.</param>
        /// <param name="options">The search options <seealso cref="IAimpAlbumArtSearchOptions" />.</param>
        /// <returns>AimpActionResult&lt;Bitmap&gt;.</returns>
        AimpActionResult<Bitmap> Get(string fileUrl, string artist, string album, IAimpAlbumArtSearchOptions options);

        /// <summary>
        /// Gets the category of provider.
        /// </summary>
        /// <returns>The <seealso cref="AimpAlbumArtProviderCategory" /></returns>
        AimpAlbumArtProviderCategory GetCategory();
    }
}
