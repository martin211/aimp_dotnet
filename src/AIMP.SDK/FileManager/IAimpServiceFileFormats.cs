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

namespace AIMP.SDK.FileManager
{
    /// <summary>
    ///     Enum FileFormats
    /// </summary>
    [Flags]
    public enum FileFormats
    {
        /// <summary>
        ///     The aimp service fileformats category audio
        /// </summary>
        AIMP_SERVICE_FILEFORMATS_CATEGORY_AUDIO = 1,

        /// <summary>
        ///     The aimp service fileformats category playlists
        /// </summary>
        AIMP_SERVICE_FILEFORMATS_CATEGORY_PLAYLISTS = 2
    }

    /// <summary>
    ///     Provide acccess to registered file types.
    ///     Implements the <see cref="AIMP.SDK.IAimpService" />
    /// </summary>
    /// <seealso cref="AIMP.SDK.IAimpService" />
    public interface IAimpServiceFileFormats : IAimpService
    {
        /// <summary>
        ///     Gets the availabel file formats.
        /// </summary>
        /// <param name="flags">The flags.</param>
        /// <returns>Operation result <seealso cref="ActionResultType" /></returns>
        AimpActionResult<string> GetFormats(FileFormats flags);

        /// <summary>
        ///     Check is the file extension supported.
        /// </summary>
        /// <param name="fileName">Name of the file.</param>
        /// <param name="flags">The flags.</param>
        /// <returns>Operation result <seealso cref="ActionResultType" /></returns>
        AimpActionResult IsSupported(string fileName, FileFormats flags);
    }
}