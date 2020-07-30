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

namespace AIMP.SDK.MusicLibrary.Extension.Command
{
    /// <summary>
    /// Interface IAimpDataStorageCommandReportDialog
    /// </summary>
    public interface IAimpDataStorageCommandReportDialog
    {
        /// <summary>
        /// Executes the specified owner handle.
        /// </summary>
        /// <param name="ownerHandle">The owner handle.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Execute(IntPtr ownerHandle);
    }
}