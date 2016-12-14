namespace AIMP.SDK.FileManager.Extensions
{
    public enum FileFormatsCategoryTypes
    {
        AIMP_SERVICE_FILEFORMATS_CATEGORY_AUDIO,
        AIMP_SERVICE_FILEFORMATS_CATEGORY_PLAYLISTS
    }

    /// <summary>
    /// Describe the new file format for player.
    /// </summary>
    public interface IAimpExtensionFileFormat
    {
        /// <summary>
        /// Returns the short description. Ex. Ogg Vorbis
        /// </summary>
        /// <param name="fileFormat">Out. The description.</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult GetDescription(string fileFormat);

        /// <summary>
        /// Returns the supported extensions. Ex. *.ogg;*.oga;
        /// </summary>
        /// <param name="extensions">Out. Supported extensions.</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult GetExtList(string extensions);

        /// <summary>
        /// Gets the supported flags.
        /// </summary>
        /// <param name="formatsCategoryTypes">Out. Supported flags <see cref="FileFormatsCategoryTypes"/>.</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult GetFlags(out FileFormatsCategoryTypes formatsCategoryTypes);
    }
}