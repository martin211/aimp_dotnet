﻿// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using AIMP.SDK.Objects;

namespace AIMP.SDK.FileManager.Commands
{
    public interface IAimpFileSystemCommandFileInfo : IAimpFileSystemCommand
    {
        /// <summary>
        /// Gets the file attributes.
        /// </summary>
        /// <param name="fileName">Name of the file.</param>
        /// <param name="attr">The attribute.</param>
        AimpActionResult GetFileAttrs(IAimpString fileName, out AimpFileAttributes attr);

        /// <summary>
        /// Gets the size of the file.
        /// </summary>
        /// <param name="file">The file.</param>
        /// <param name="size">The size.</param>
        AimpActionResult GetFileSize(IAimpString file, out long size);

        /// <summary>
        /// Determines whether [is file exists] [the specified file].
        /// </summary>
        /// <param name="file">The file.</param>
        AimpActionResult IsFileExists(IAimpString file);
    }
}