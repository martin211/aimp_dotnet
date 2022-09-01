//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;

namespace AIMP.SDK.FileManager
{
    /// <summary>
    /// Enum FileFormats
    /// </summary>
    [Flags]
    public enum FileFormats
    {
        /// <summary>
        /// The aimp service fileformats category audio
        /// </summary>
        Audio = 1,

        /// <summary>
        /// The aimp service fileformats category playlists
        /// </summary>
        Playlists = 2
    }

    /// <summary>
    /// Provide acccess to registered file types.
    /// Implements the <see cref="AIMP.SDK.IAimpService" />
    /// </summary>
    /// <seealso cref="AIMP.SDK.IAimpService" />
    public interface IAimpServiceFileFormats : IAimpService
    {
        /// <summary>
        /// Gets the availabel file formats.
        /// </summary>
        /// <param name="flags">The flags.</param>
        /// <returns>AimpActionResult&lt;System.String&gt;.</returns>
        AimpActionResult<string> GetFormats(FileFormats flags);

        /// <summary>
        /// Check is the file extension supported.
        /// </summary>
        /// <param name="fileName">Name of the file.</param>
        /// <param name="flags">The flags.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult IsSupported(string fileName, FileFormats flags);
    }
}
