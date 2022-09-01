//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;

namespace AIMP.SDK.MusicLibrary.Extension.Command
{
    /// <summary>
    /// Interface IAimpDataStorageCommandAddFilesDialog
    /// </summary>
    public interface IAimpDataStorageCommandAddFilesDialog
    {
        /// <summary>
        /// Executes the specified owner handle.
        /// </summary>
        /// <param name="ownerHandle">The owner window handle.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Execute(IntPtr ownerHandle);
    }
}
