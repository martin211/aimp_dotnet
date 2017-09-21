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
        /// <summary>
        /// This is a user data parameter, it allow you to bind custom data to the interface.
        /// </summary>
        string Custom { get; set; }

        /// <summary>
        /// Internal field name, this values used as unique ID of field in space of current data storage.
        /// Display name for the field gets from the custom localization from the AIMPML\<FieldName> key path.
        /// </summary>
        string Name { get; set; }

        /// <summary>
        /// Gets or sets the data field type.
        /// </summary>
        AimpDataFieldType Type { get; set; }

        /// <summary>
        /// Gets or sets the data field flags.
        /// </summary>
        AimpDataFieldFlagsType Flags { get; set; }

        /// <summary>
        /// Gets or sets the field image.
        /// </summary>
        ImageType Image { get; set; }

        /// <summary>
        /// Gets or sets the display value.
        /// </summary>
        string DisplayValue { get; set; }
    }

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