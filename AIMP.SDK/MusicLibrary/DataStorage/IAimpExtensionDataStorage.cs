using System;
using System.Collections;
using AIMP.SDK.MusicLibrary.Presets;

namespace AIMP.SDK.MusicLibrary.DataStorage
{
    [Flags]
    public enum CapabilitiesFlags
    {
        Filtering,
        GroupingPreset,
        PreImages
    }

    public enum SchemaType
    {
        All,
        GroupingTree,
        TableGroupBy,
        TableGroupDetails,
        TableViewDefault,
        TableViewAlbumThumbnails
    }

    public interface IAimpExtensionDataStorage
    {
        string Id { get; }

        string Caption { get; }

        void Initialize(IAimpDataStorageManager dataStorageManager);

        void Finalize();

        void FlushCache();

        //AimpActionResult ConfigLoad(IAimpConfig config, string section);

        //AimpActionResult ConfigSave(IAimpConfig config, string section);

        AimpActionResult GetFields(SchemaType schema, out ICollection list);

        AimpActionResult GetGroupingPresets(SchemaType schema, out IAimpGroupingPresets preset);
    }
}