//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using AIMP.SDK.AlbumArt;
using AIMP.SDK.Objects;

namespace AIMP.SDK.MusicLibrary.Extension;

/// <summary>
/// This interface implements image provider for group details and thumbnails in music library that provided via plugin. Unlike IAimpServiceAlbumArt this provider works with unique data from the music library.
/// The interface must be implemented by plugin on same level as the <see cref="IAimpExtensionDataStorage"/> interface.
/// Interface implementation must support asynchronous access.
/// </summary>
public interface IAimpAlbumArtProvider2
{
    /// <summary>
    /// Gets the <see cref="IAimpImageContainer"/>.
    /// </summary>
    /// <param name="fields">List of field names presented as string that contains a Required flag in the Flags property value. </param>
    /// <param name="values">Array o values. Size of array is same value of the Fields.GetCount method result. Contains values for the Fields based on first file in group</param>
    AimpActionResult<IAimpImageContainer> Get(IAimpObjectList<string> fields, object[] values, IAimpAlbumArtRequest request);
}