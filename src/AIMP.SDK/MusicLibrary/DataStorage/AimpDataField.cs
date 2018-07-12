namespace AIMP.SDK.MusicLibrary.DataStorage
{
    public class AimpDataField : IAimpDataField
    {
        public const string AIMPML_RESERVED_FIELD_ID = "ID";
        public const string AIMPML_RESERVED_FIELD_FILENAME = "FileName"; // !REQUIRED! string
        public const string AIMPML_RESERVED_FIELD_FILESIZE = "FileSize"; // Int64, in bytes
        public const string AIMPML_RESERVED_FIELD_DURATION = "Duration"; // double, in seconds
        public const string AIMPML_RESERVED_FIELD_USERMARK = "UserMark"; // double, 0.0 .. 5.0

        public AimpDataField(string name, AimpDataFieldType type,
            AimpDataFieldFlagsType flags = AimpDataFieldFlagsType.None)
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