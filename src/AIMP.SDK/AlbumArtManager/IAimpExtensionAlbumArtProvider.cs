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

namespace AIMP.SDK.AlbumArtManager
{
    using System.Drawing;

    public enum AimpAlbumArtProviderCategory
    {
        AIMP_ALBUMART_PROVIDER_CATEGORY_TAGS,

        AIMP_ALBUMART_PROVIDER_CATEGORY_FILE,

        AIMP_ALBUMART_PROVIDER_CATEGORY_INTERNET
    }

    /// <summary>
    /// Interface allows for the plugin to register custom album art provider.
    /// </summary>
    /// <seealso cref="AIMP.SDK.AlbumArtManager.IAimpExtensionAlbumArtProvider2" />
    /// <seealso cref="AIMP.SDK.IAimpExtension" />
    public interface IAimpExtensionAlbumArtProvider : IAimpExtensionAlbumArtProvider2, IAimpExtension
    {
        /// <summary>
        /// Gets the album art image.
        /// </summary>
        /// <param name="fileUrl">The file URL.</param>
        /// <param name="artist">Optional. The artist.</param>
        /// <param name="album">Optional.The album.</param>
        /// <param name="options">The search options <seealso cref="IAimpAlbumArtSearchOptions"/>.</param>
        /// <param name="image">Out. The album art image.</param>
        /// <returns>The <see cref="ActionResultType"/> result.</returns>
        AimpActionResult<Bitmap> Get(string fileUrl, string artist, string album, IAimpAlbumArtSearchOptions options);

        /// <summary>
        /// Gets the category of provider.
        /// </summary>
        /// <returns>The <seealso cref="AimpAlbumArtProviderCategory"/></returns>
        AimpAlbumArtProviderCategory GetCategory();
    }
}