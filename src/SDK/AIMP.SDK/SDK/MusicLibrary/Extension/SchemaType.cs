using System;
using AIMP.SDK.MusicLibrary.DataStorage;

namespace AIMP.SDK.MusicLibrary.Extension;

/// <summary>
/// Enum SchemaType
/// </summary>
public enum SchemaType
{
    /// <summary>
    /// List of all available fields in data storage.
    /// The property <see cref="IAimpExtensionDataStorage.GetFields" /> must contains an <see cref="IAimpDataField" />
    /// objects.
    /// </summary>
    All = 0,

    /// <summary>
    /// List of fields that used for grouping in table.
    /// If list is empty - the Group Details and the Album Thumbnails views will not be available for the end user.
    /// The property <see cref="IAimpExtensionDataStorage.GetFields" /> must contains an string objects with field names.
    /// </summary>
    TableGroupby = 2,

    /// <summary>
    /// The grouping tree
    /// </summary>
    [Obsolete("Value not found at documentation and SDK.")]
    GroupingTree = 1,

    /// <summary>
    /// List of fields that displays in group details area.
    /// The property <see cref="IAimpExtensionDataStorage.GetFields" /> must contains an string objects with field names.
    /// </summary>
    TableGroupDetails = 3,

    /// <summary>
    /// List of fields that displays to end user in table by default in Default view.
    /// The property <see cref="IAimpExtensionDataStorage.GetFields" /> must contains an string objects with field names.
    /// </summary>
    TableViewDefault = 10,

    /// <summary>
    /// list of fields that displays to end user in table by default in Group Details view.
    /// The property <see cref="IAimpExtensionDataStorage.GetFields" /> must contains an string objects with field names.
    /// </summary>
    TableViewGroupDetails = 11,

    /// <summary>
    /// List of fields that displays to end user in table by default in Album Thumbnails view.
    /// The property <see cref="IAimpExtensionDataStorage.GetFields" /> must contains an string objects with field names.
    /// </summary>
    TableViewAlbumThumbnails = 12
}