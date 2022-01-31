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

namespace AIMP.SDK.FileManager.Extensions
{
    /// <summary>
    /// Enum FileFormatsCategoryTypes
    /// </summary>
    public enum FileFormatsCategoryTypes
    {
        /// <summary>
        /// The aimp service fileformats category audio
        /// </summary>
        Audio,

        /// <summary>
        /// The aimp service fileformats category playlists
        /// </summary>
        Playlists
    }

    /// <summary>
    /// Extension for the <seealso cref="IAimpServiceFileFormats" /> service that provides an information about the new
    /// file format.
    /// <para>
    /// Instance should be created by plugin and must be registered in the application at the plugin initialization
    /// method via the IAimpCore.RegisterExtension method.
    /// </para>
    /// Implements the <see cref="AIMP.SDK.IAimpExtension" />
    /// </summary>
    /// <seealso cref="AIMP.SDK.IAimpExtension" />
    public interface IAimpExtensionFileFormat : IAimpExtension
    {
        /// <summary>
        /// Returns the short description. Ex. Ogg Vorbis
        /// </summary>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult<string> Description { get; }

        /// <summary>
        /// Returns the supported extensions. Ex. *.ogg;*.oga;
        /// </summary>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult<string> ExtList { get; }

        /// <summary>
        /// Gets the supported flags.
        /// </summary>
        /// <returns>AimpActionResult&lt;FileFormatsCategoryTypes&gt;.</returns>
        AimpActionResult<FileFormatsCategoryTypes> Flags { get; }
    }
}
