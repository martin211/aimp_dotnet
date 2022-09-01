//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;
using System.Collections.Generic;
using AIMP.SDK.FileManager.Objects;

namespace AIMP.SDK.FileManager.Extensions
{
    /// <summary>
    /// Interface is an extension for the <see cref="IAimpServiceFileManager" /> service that allows split real file
    /// container into one or view virtual files.
    /// <para>
    /// Instance should be created by plugin and must be registered in the application at the plugin initialization
    /// method via the IAimpCore.RegisterExtension method.
    /// </para>
    /// </summary>
    public interface IAimpExtensionFileExpander : IAimpExtension
    {
        /// <summary>
        /// Split the file container to virtual files.
        /// </summary>
        /// <param name="fileName">The real file name</param>
        /// <param name="progressCallback">Progress callback <see cref="IAimpProgressCallback"/>.</param>
        /// <returns>AimpActionResult&lt;IList&lt;IAimpVirtualFile&gt;&gt;.</returns>
        AimpActionResult<IAimpObjectList<IAimpVirtualFile>> Expand(string fileName, IAimpProgressCallback progressCallback);
    }
}
