﻿//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System.Collections.Generic;
using AIMP.SDK.FileManager.Objects;
using AIMP.SDK.Threading;

namespace AIMP.SDK.TagEditor.Extensions;

/// <summary>
/// AimpServiceFindTagsOnlineAlbumInfoReceiveProc is a callback function that returns found album to tag editor.
/// Plugin able to call this function few times depended how much results are found. 
/// </summary>
public delegate void AimpServiceFindTagsOnlineAlbumInfoReceiveProc(IAimpFileInfo fileInfo, object userData);

/// <summary>
/// Extension for the IAimpServiceFindTagsOnline service, provides an ability to implement custom tags provider for the "autotagging via online-services" feature that available in advanced tag editor.
/// </summary>
public interface IAimpExtensionTagsProvider
{
    /// <summary>
    /// Gets the name.
    /// </summary>
    AimpActionResult<string> GetName();

    /// <summary>
    /// Returns list of the tag fields that are supported by provider.
    /// </summary>
    AimpActionResult<IList<IAimpFileInfo>> GetSupportedFields();


    /// <summary>
    /// Find albums by user query.
    /// Method will be called from non-main thread!
    /// </summary>
    /// <param name="query">The query.</param>
    /// <param name="owner">The owner.</param>
    /// <param name="error">Plugin must populate error info only if unexpected error happened.</param>
    /// <param name="callback">The callback.</param>
    /// <param name="userData">The user data.</param>
    AimpActionResult FindAlbums(string query, IAimpTaskOwner owner, IAimpErrorInfo error, AimpServiceFindTagsOnlineAlbumInfoReceiveProc callback, object userData);

    /// <summary>
    /// Provides the list of tracks by AlbumInfo that provided via the FindAlbums method.
    /// You can pass the custom data to AlbumInfo via IAIMPFileInfo.AIMP_FILEINFO_PROPID_CUSTOM.
    /// Method will be called from non-main thread! 
    /// </summary>
    AimpActionResult<IAimpObjectList<IAimpFileInfo>> FindTracks(string query, IAimpTaskOwner owner, IAimpErrorInfo error);
}
