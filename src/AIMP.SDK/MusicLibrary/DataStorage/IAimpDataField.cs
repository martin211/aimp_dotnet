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
    /// <summary>
    /// Enum AimpDataFieldType
    /// </summary>
    public enum AimpDataFieldType
    {
        /// <summary>
        /// The none
        /// </summary>
        None = 0,
        /// <summary>
        /// The int32
        /// </summary>
        Int32 = 1,
        /// <summary>
        /// The int64
        /// </summary>
        Int64 = 2,
        /// <summary>
        /// The float
        /// </summary>
        Float = 3,
        /// <summary>
        /// The string
        /// </summary>
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

    /// <summary>
    /// Enum AimpDataFieldFlagsType
    /// </summary>
    [Flags]
    public enum AimpDataFieldFlagsType
    {
        /// <summary>
        /// The none
        /// </summary>
        None = 0,
        /// <summary>
        /// The grouping
        /// </summary>
        Grouping = 1,
        /// <summary>
        /// The filtering
        /// </summary>
        Filtering = 2,
        /// <summary>
        /// The internal
        /// </summary>
        Internal = 4,
        /// <summary>
        /// The required
        /// </summary>
        Required = 8
    }

    /// <summary>
    /// Enum ImageType
    /// </summary>
    public enum ImageType
    {
        /// <summary>
        /// The folder
        /// </summary>
        Folder = 0,
        /// <summary>
        /// The artist
        /// </summary>
        Artist = 1,
        /// <summary>
        /// The disk
        /// </summary>
        Disk = 2,
        /// <summary>
        /// The note
        /// </summary>
        Note = 3,
        /// <summary>
        /// The star
        /// </summary>
        Star = 4,
        /// <summary>
        /// The calendar
        /// </summary>
        Calendar = 5,
        /// <summary>
        /// The label
        /// </summary>
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
        /// <value>The custom.</value>
        string Custom { get; set; }

        /// <summary>
        /// Gets or sets the name.
        /// </summary>
        /// <value>The name.</value>
        string Name { get; set; }

        /// <summary>
        /// Gets or sets the data field type.
        /// </summary>
        /// <value>The type.</value>
        AimpDataFieldType Type { get; set; }

        /// <summary>
        /// Gets or sets the data field flags.
        /// </summary>
        /// <value>The flags.</value>
        AimpDataFieldFlagsType Flags { get; set; }

        /// <summary>
        /// Gets or sets the field image.
        /// </summary>
        /// <value>The image.</value>
        ImageType Image { get; set; }

        /// <summary>
        /// Gets or sets the display value.
        /// </summary>
        /// <value>The display value.</value>
        string DisplayValue { get; set; }
    }
}