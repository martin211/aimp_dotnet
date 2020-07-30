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

using System.Collections.Generic;

namespace AIMP.SDK.FileManager.Commands
{
    /// <summary>
    /// Interface IAimpFileSystemCommandCopyToClipboard
    /// Implements the <see cref="AIMP.SDK.FileManager.Commands.IAimpFileSystemCommand" />
    /// </summary>
    /// <seealso cref="AIMP.SDK.FileManager.Commands.IAimpFileSystemCommand" />
    public interface IAimpFileSystemCommandCopyToClipboard : IAimpFileSystemCommand
    {
        /// <summary>
        /// Copies to clipboard.
        /// </summary>
        /// <param name="files">The files.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult CopyToClipboard(List<string> files);
    }
}