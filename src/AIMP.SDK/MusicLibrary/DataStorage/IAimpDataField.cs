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

using System;

namespace AIMP.SDK.MusicLibrary.DataStorage
{
    public enum AimpDataFieldType
    {
        None = 0,
        Int32 = 1,
        Int64 = 2,
        Float = 3,
        String = 4,

        /// <summary>
        /// Display value is formatted data time value (format string is depended from the context).
        /// </summary>
        DateTime = 10,

        /// <summary>
        /// Display value is formatted time value (format string is depended from the context).
        /// </summary>
        Duration = 11,

        /// <summary>
        /// Display value is formatted file size value (format string is depended from the context).
        /// </summary>
        FileSize = 12,

        /// <summary>
        /// Grouping tree split the value by levels by the "\" and "/" characters. Grouping by this field with other fields is not available.
        /// </summary>
        FileName = 13
    }

    [Flags]
    public enum AimpDataFieldFlagsType
    {
        None = 0,
        Grouping = 1,
        Filtering = 2,
        Internal = 4,
        Required = 8
    }

    public enum ImageType
    {
        Folder = 0,
        Artist = 1,
        Disk = 2,
        Note = 3,
        Star = 4,
        Calendar = 5,
        Label = 6
    }

    /// <summary>
    /// Provides information about the data field for Music Library.
    /// </summary>
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
}