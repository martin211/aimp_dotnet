// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using System;
using System.Collections;
using AIMP.SDK.MusicLibrary.Presets;

namespace AIMP.SDK.MusicLibrary.Extension
{
    [Flags]
    public enum CapabilitiesType
    {
        AIMPML_DATASTORAGE_CAP_FILTERING = 1,
        AIMPML_DATASTORAGE_CAP_PREIMAGES = 2,
        AIMPML_DATASTORAGE_CAP_GROUPINGPRESETS = 4
    }

    public enum SchemaType
    {
        /// <summary>
        /// List of all available fields in data storage.
        /// The property <see cref="IAimpExtensionDataStorage.GetFields"/> must contains an <see cref="IAimpDataField"/> objects.
        /// </summary>
        AIMPML_FIELDS_SCHEMA_ALL = 0,

        /// <summary>
        /// List of fields that used for grouping in table.
        /// If list is empty - the Group Details and the Album Thumbnails views will not be available for the end user.
        /// The property <see cref="IAimpExtensionDataStorage.GetFields"/> must contains an string objects with field names.
        /// </summary>
        AIMPML_FIELDS_SCHEMA_TABLE_GROUPBY = 2,

        [Obsolete("Value not found at documentation and SDK.")]
        AIMPML_FIELDS_SCHEMA_GROUPING_TREE = 1,

        /// <summary>
        /// List of fields that displays in group details area.
        /// The property <see cref="IAimpExtensionDataStorage.GetFields"/> must contains an string objects with field names.
        /// </summary>
        AIMPML_FIELDS_SCHEMA_TABLE_GROUPDETAILS = 3,

        /// <summary>
        /// List of fields that displays to end user in table by default in Default view.
        /// The property <see cref="IAimpExtensionDataStorage.GetFields"/> must contains an string objects with field names.
        /// </summary>
        AIMPML_FIELDS_SCHEMA_TABLE_VIEW_DEFAULT = 10,

        /// <summary>
        /// list of fields that displays to end user in table by default in Group Details view.
        /// The property <see cref="IAimpExtensionDataStorage.GetFields"/> must contains an string objects with field names.
        /// </summary>
        AIMPML_FIELDS_SCHEMA_TABLE_VIEW_GROUPDETAILS = 11,

        /// <summary>
        /// List of fields that displays to end user in table by default in Album Thumbnails view.
        /// The property <see cref="IAimpExtensionDataStorage.GetFields"/> must contains an string objects with field names.
        /// </summary>
        AIMPML_FIELDS_SCHEMA_TABLE_VIEW_ALBUMTHUMBNAILS = 12
    }

    public enum GroupingPresetsSchemaType
    {
        AIMPML_GROUPINGPRESETS_SCHEMA_BUILTIN = 1,
        AIMPML_GROUPINGPRESETS_SCHEMA_DEFAULT = 2
    }

    /// <summary>
    /// The extension for the <see cref="IAimpServiceMusicLibrary"/> service provides an ability to plugin to implement custom data storage for the Music Library.
    /// Interface implementation must support asynchronous access.
    /// <para>
    /// Data storage MUST contains a fields with following names:
    /// AIMPML_RESERVED_FIELD_ID - unique ID of record in data storage
    /// AIMPML_RESERVED_FIELD_FILENAME - file name of the record that used by player
    /// If this fields are not defined in Data Storage - registration of the extension will be failed.
    /// 
    /// Also, the Music Library engine provides an ability to use following special fields:
    /// AIMPML_RESERVED_FIELD_FILESIZE - file size in bytes (type: Int64), used to calculate information about the content of table
    /// AIMPML_RESERVED_FIELD_DURATION - duration in seconds (type: Double) ,used to calculate information about the content of table
    /// AIMPML_RESERVED_FIELD_USERMARK - user rating mark (type: Double), Refer to the IAIMPMLDataStorageCommandUserMark
    /// </para>
    /// </summary>
    public interface IAimpExtensionDataStorage
    {
        /// <summary>
        /// Gets the storage identifier.
        /// </summary>
        string Id { get; }

        /// <summary>
        /// Gets the storage title.
        /// </summary>
        string Caption { get; }

        CapabilitiesType Capabilities { get; }

        /// <summary>
        /// Method calls after succeeded registration of data storage.
        /// </summary>
        /// <param name="manager">The Manager interface is used to notify the Music Library about the changes in data storage.</param>
        void Initialize(IAimpDataStorageManager manager);

        /// <summary>
        /// Method calls before the finalization of plugin.
        /// Plugin must dispose all external links.
        /// </summary>
        void Terminate(); // TODO Rename

        /// <summary>
        /// Method calls when user executes the "refresh" command via hotkey or context menu.
        /// After this call the Music Library engine will automatically reload the data from data storage.
        /// </summary>
        void FlushCache();

        /// <summary>
        /// Method will be called on first activation of tab of data storage in Music Library interface.
        /// </summary>
        /// <param name="config">The configuration.</param>
        /// <param name="section">Section Name to that contains the settings.
        /// You can use the children section names if it needed: Section + "." + ChildSectionName</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult ConfigLoad(IAimpConfig config, string section);

        /// <summary>
        /// Method calls before the finalization of plugin.
        /// </summary>
        /// <param name="config">The configuration.</param>
        /// <param name="section">Section Name to store the settings.
        /// You can use the children section names if it needed: Section + "." + ChildSectionName</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult ConfigSave(IAimpConfig config, string section);

        /// <summary>
        /// Method returns settings and layout of the data fields in dependency from specified Schema value.
        /// </summary>
        /// <param name="schemaType">Type of the schema <see cref="SchemaType"/>.</param>
        /// <param name="list">The list.</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult GetFields(SchemaType schemaType, out IList list);

        /// <summary>
        /// Plugin must populate the Presets list by predefined presets for grouping tree based on the Schema value.
        /// </summary>
        /// <param name="schema">The schema.</param>
        /// <param name="presets">The presets.</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult GetGroupingPresets(GroupingPresetsSchemaType schema, IAimpGroupingPresets presets);
    }
}