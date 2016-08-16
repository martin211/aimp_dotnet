using System;
using System.Collections;
using AIMP.SDK.MusicLibrary.Presets;

namespace AIMP.SDK.MusicLibrary.Extension
{
    [Flags]
    public enum CapabilitiesType
    {
        AIMPML_DATASTORAGE_CAP_FILTERING,
        AIMPML_DATASTORAGE_CAP_GROUPINGPRESETS,
        AIMPML_DATASTORAGE_CAP_PREIMAGES
    }

    public enum SchemaType
    {
        AIMPML_FIELDS_SCHEMA_ALL,
        AIMPML_FIELDS_SCHEMA_GROUPING_TREE,
        AIMPML_FIELDS_SCHEMA_TABLE_GROUPBY,
        AIMPML_FIELDS_SCHEMA_TABLE_GROUPDETAILS,
        AIMPML_FIELDS_SCHEMA_TABLE_VIEW_DEFAULT,
        AIMPML_FIELDS_SCHEMA_TABLE_VIEW_GROUPDETAILS,
        AIMPML_FIELDS_SCHEMA_TABLE_VIEW_ALBUMTHUMBNAILS,
        AIMPML_RESERVED_FIELD_ID,
        AIMPML_RESERVED_FIELD_FILENAME,
        AIMPML_RESERVED_FIELD_FILESIZE,
        AIMPML_RESERVED_FIELD_DURATION,
        AIMPML_RESERVED_FIELD_USERMARK
    }

    public enum GroupingPresetsSchemaType
    {
        AIMPML_GROUPINGPRESETS_SCHEMA_BUILTIN,
        AIMPML_GROUPINGPRESETS_SCHEMA_DEFAULT
    }

    /// <summary>
    /// Data storage extension.
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
        /// Initializes callback.
        /// </summary>
        /// <param name="manager">The manager.</param>
        void Initialize(IAimpDataStorageManager manager);

        /// <summary>
        /// Finalizes callback.
        /// </summary>
        void Dispose();

        void FlushCache();

        AimpActionResult ConfigLoad(IAimpConfig config, string section);

        AimpActionResult ConfigSave(IAimpConfig config, string section);

        AimpActionResult GetFields(SchemaType schemaType, out IList list);

        AimpActionResult GetGroupingPresets(GroupingPresetsSchemaType schema, IAimpGroupingPresets presets);
    }
}