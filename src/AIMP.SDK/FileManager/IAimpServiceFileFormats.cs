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
using System;

namespace AIMP.SDK.FileManager
{
    [Flags]
    public enum FileFormats
    {
        AIMP_SERVICE_FILEFORMATS_CATEGORY_AUDIO = 1,
        AIMP_SERVICE_FILEFORMATS_CATEGORY_PLAYLISTS = 2
    }

    /// <summary>
    /// Provide acccess to registered file types.
    /// </summary>
    public interface IAimpServiceFileFormats : IAimpService
    {
        /// <summary>
        /// Gets the availabel file formats.
        /// </summary>
        /// <param name="flags"></param>
        /// <param name="formats">Out. File formats.</param>
        /// <returns>Operation result <seealso cref="ActionResultType"/></returns>
        ActionResultType GetFormats(FileFormats flags, out string formats);

        /// <summary>
        /// Check is the file extension supported.
        /// </summary>
        /// <param name="fileName"></param>
        /// <param name="flags"></param>
        /// <returns>Operation result <seealso cref="ActionResultType"/></returns>
        ActionResultType IsSupported(string fileName, FileFormats flags);
    }
}