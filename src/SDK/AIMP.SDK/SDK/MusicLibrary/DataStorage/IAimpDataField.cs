namespace AIMP.SDK.MusicLibrary.DataStorage;

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