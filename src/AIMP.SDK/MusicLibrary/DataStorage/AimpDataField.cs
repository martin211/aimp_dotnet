// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

namespace AIMP.SDK.MusicLibrary.DataStorage
{
    /// <summary>
    /// Class AimpDataField.
    /// Implements the <see cref="AIMP.SDK.MusicLibrary.DataStorage.IAimpDataField" />
    /// </summary>
    /// <seealso cref="AIMP.SDK.MusicLibrary.DataStorage.IAimpDataField" />
    public class AimpDataField : IAimpDataField
    {
        /// <summary>
        /// The aimpml reserved field identifier
        /// </summary>
        public static readonly string AIMPML_RESERVED_FIELD_ID = "ID";

        /// <summary>
        /// The aimpml reserved field filename
        /// </summary>
        public static readonly string AIMPML_RESERVED_FIELD_FILENAME = "FileName"; // !REQUIRED! string

        /// <summary>
        /// The aimpml reserved field filesize
        /// </summary>
        public static readonly string AIMPML_RESERVED_FIELD_FILESIZE = "FileSize"; // Int64, in bytes

        /// <summary>
        /// The aimpml reserved field duration
        /// </summary>
        public static readonly string AIMPML_RESERVED_FIELD_DURATION = "Duration"; // double, in seconds

        /// <summary>
        /// The aimpml reserved field usermark
        /// </summary>
        public static readonly string AIMPML_RESERVED_FIELD_USERMARK = "UserMark"; // double, 0.0 .. 5.0

        /// <summary>
        /// Initializes a new instance of the <see cref="AimpDataField" /> class.
        /// </summary>
        /// <param name="name">The name.</param>
        /// <param name="type">The type.</param>
        /// <param name="flags">The flags.</param>
        public AimpDataField(string name, AimpDataFieldType type,
            AimpDataFieldFlagsType flags = AimpDataFieldFlagsType.None)
        {
            Name = name;
            Type = type;
            Flags = flags;
        }

        /// <summary>
        /// Gets or sets the user data. That data will be attached to the instance of interface.
        /// </summary>
        /// <value>The custom.</value>
        public string Custom { get; set; }

        /// <summary>
        /// Gets or sets the name.
        /// </summary>
        /// <value>The name.</value>
        public string Name { get; set; }

        /// <summary>
        /// Gets or sets the type of field <see cref="AimpDataFieldType" />.
        /// </summary>
        /// <value>The type.</value>
        public AimpDataFieldType Type { get; set; }

        /// <summary>
        /// Gets or sets the data field flags.
        /// </summary>
        /// <value>The flags.</value>
        public AimpDataFieldFlagsType Flags { get; set; }

        /// <summary>
        /// Gets or sets the field image.
        /// </summary>
        /// <value>The image.</value>
        public ImageType Image { get; set; }

        /// <summary>
        /// Gets or sets the display value.
        /// </summary>
        /// <value>The display value.</value>
        public string DisplayValue { get; set; }
    }
}