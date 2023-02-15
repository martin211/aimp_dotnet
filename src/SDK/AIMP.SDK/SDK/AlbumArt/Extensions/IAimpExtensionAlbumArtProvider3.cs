//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using AIMP.SDK.FileManager.Objects;
using AIMP.SDK.Objects;

namespace AIMP.SDK.AlbumArt.Extensions;

/// <summary>
/// 
/// </summary>
/// <seealso cref="AIMP.SDK.IAimpExtension" />
public interface IAimpExtensionAlbumArtProvider3 : IAimpExtension
{
    /// <summary>
    /// Gets the album art image.
    /// </summary>
    /// <param name="file">The file info.</param>
    /// <param name="requestOption">The request option.</param>
    AimpActionResult<IAimpImageContainer> Get(IAimpFileInfo file, IAimpAlbumArtRequest requestOption);

    AimpAlbumArtProviderCategory GetCategory();
}