using System;

namespace AIMP.SDK.MusicLibrary.DataStorage
{
    public enum AimpDataFieldType
    {
        None = 0,
        AIMPML_FIELDTYPE_INT32 = 1,
        AIMPML_FIELDTYPE_INT64 = 2,
        AIMPML_FIELDTYPE_FLOAT = 3,
        AIMPML_FIELDTYPE_STRING = 4,
        AIMPML_FIELDTYPE_DATETIME = 10,
        AIMPML_FIELDTYPE_DURATION = 11,
        AIMPML_FIELDTYPE_FILESIZE = 12,
        AIMPML_FIELDTYPE_FILENAME = 13
    }

    [Flags]
    public enum AimpDataFieldFlagsType
    {
        None = 0,
        AIMPML_FIELDFLAG_GROUPING = 1,
        AIMPML_FIELDFLAG_FILTERING = 2,
        AIMPML_FIELDFLAG_INTERNAL = 4,
        AIMPML_FIELDFLAG_REQUIRED = 8
    }

    public enum ImageType
    {
        AIMPML_FIELDIMAGE_FOLDER = 0,
        AIMPML_FIELDIMAGE_ARTIST = 1,
        AIMPML_FIELDIMAGE_DISK = 2,
        AIMPML_FIELDIMAGE_NOTE = 3,
        AIMPML_FIELDIMAGE_STAR = 4,
        AIMPML_FIELDIMAGE_CALENDAR = 5,
        AIMPML_FIELDIMAGE_LABEL = 6
    }

    public interface IAimpDataField
    {
        string Custom { get; set; }

        string Name { get; set; }

        AimpDataFieldType Type { get; set; }

        AimpDataFieldFlagsType Flags { get; set; }

        ImageType Image { get; set; }

        string DisplayValue { get; set; }
    }

    public class AimpDataField : IAimpDataField
    {
        public AimpDataField(string name, AimpDataFieldType type, AimpDataFieldFlagsType flags = AimpDataFieldFlagsType.None)
        {
            Name = name;
            Type = type;
            Flags = flags;
        }

        public string Custom { get; set; }
        public string Name { get; set; }
        public AimpDataFieldType Type { get; set; }
        public AimpDataFieldFlagsType Flags { get; set; }
        public ImageType Image { get; set; }
        public string DisplayValue { get; set; }
    }
}