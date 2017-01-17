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
        AIMPML_FIELDS_SCHEMA_ALL = 0,
        AIMPML_FIELDS_SCHEMA_GROUPING_TREE = 1,
        AIMPML_FIELDS_SCHEMA_TABLE_GROUPBY = 2,
        AIMPML_FIELDS_SCHEMA_TABLE_GROUPDETAILS = 3,
        AIMPML_FIELDS_SCHEMA_TABLE_VIEW_DEFAULT = 10,
        AIMPML_FIELDS_SCHEMA_TABLE_VIEW_GROUPDETAILS = 11,
        AIMPML_FIELDS_SCHEMA_TABLE_VIEW_ALBUMTHUMBNAILS = 12
    }

    public enum GroupingPresetsSchemaType
    {
        AIMPML_GROUPINGPRESETS_SCHEMA_BUILTIN = 1,
        AIMPML_GROUPINGPRESETS_SCHEMA_DEFAULT = 2
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
        void Terminate(); // TODO Rename

        void FlushCache();

        AimpActionResult ConfigLoad(IAimpConfig config, string section);

        AimpActionResult ConfigSave(IAimpConfig config, string section);

        AimpActionResult GetFields(SchemaType schemaType, out IList list);

        AimpActionResult GetGroupingPresets(GroupingPresetsSchemaType schema, IAimpGroupingPresets presets);
    }
}