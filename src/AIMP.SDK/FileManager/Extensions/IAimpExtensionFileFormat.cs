// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------
namespace AIMP.SDK.FileManager.Extensions
{
    public enum FileFormatsCategoryTypes
    {
        AIMP_SERVICE_FILEFORMATS_CATEGORY_AUDIO,
        AIMP_SERVICE_FILEFORMATS_CATEGORY_PLAYLISTS
    }

    /// <summary>
    /// Extension for the <seealso cref="IAimpServiceFileFormats"/> service that provides an information about the new file format.
    /// <para>
    /// Instance should be created by plugin and must be registered in the application at the plugin initialization method via the IAimpCore.RegisterExtension method.
    /// </para>
    /// </summary>
    public interface IAimpExtensionFileFormat : IAimpExtension
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